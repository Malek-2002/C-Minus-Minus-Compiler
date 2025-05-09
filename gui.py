#!/usr/bin/env python3
import os
import subprocess
import csv
import gi
gi.require_version('Gtk', '3.0')
gi.require_version('GtkSource', '4')
from gi.repository import Gtk, GtkSource, GLib, Pango, Gdk, GdkPixbuf

class ClacCompilerApp(Gtk.Application):
    def __init__(self):
        super().__init__(application_id="com.example.clac")
        self.connect("activate", self.on_activate)
        
    def on_activate(self, app):
        self.win = ClacCompilerWindow(application=app)
        self.win.present()

class ClacCompilerWindow(Gtk.ApplicationWindow):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        
        # Window setup
        self.set_title("C Minus Minus Compiler")
        self.set_default_size(1200, 1000)
        self.set_border_width(10)
        
        # Set default theme mode (light)
        self.dark_mode = False
        
        # Initialize UI
        self.setup_ui()
        
        # Load input.txt if it exists
        if os.path.exists("./data/input.txt"):
            self.load_file("./data/input.txt")
        
        self.show_all()
    
    def setup_ui(self):
        # Main container - vertical box
        main_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
        self.add(main_box)
        
        # Header with logo, title and theme switch
        header_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        main_box.pack_start(header_box, False, False, 0)
        
        # Logo 
        self.logo_image = Gtk.Image()
        # Try to load logo if it exists
        try:
            if os.path.exists("logo.png"):
                pixbuf = GdkPixbuf.Pixbuf.new_from_file_at_scale("logo.png", 64, 64, True)
                self.logo_image.set_from_pixbuf(pixbuf)
        except Exception as e:
            print(f"Error loading logo: {e}")
        
        header_box.pack_start(self.logo_image, False, False, 0)
        
        # Title label with styling
        title_label = Gtk.Label()
        title_label.set_markup("<span font_desc='16' weight='bold'>C Minus Minus Compiler</span>")
        header_box.pack_start(title_label, True, False, 0)
        
        # Dark mode switch
        mode_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=5)
        mode_label = Gtk.Label(label="Dark Mode")
        mode_box.pack_start(mode_label, False, False, 0)
        
        self.theme_switch = Gtk.Switch()
        self.theme_switch.connect("notify::active", self.on_theme_switched)
        mode_box.pack_start(self.theme_switch, False, False, 0)
        
        header_box.pack_end(mode_box, False, False, 0)
        
        # Create paned container for editor and output
        paned = Gtk.Paned(orientation=Gtk.Orientation.VERTICAL)
        main_box.pack_start(paned, True, True, 0)
        
        # ===== Input Editor Section =====
        editor_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=5)
        
        # Editor label
        editor_label = Gtk.Label()
        editor_label.set_markup("<b>Input File Editor</b>")
        editor_label.set_halign(Gtk.Align.START)
        editor_box.pack_start(editor_label, False, False, 0)
        
        # Create source view with syntax highlighting
        self.create_source_view()
        editor_box.pack_start(self.source_scroll, True, True, 0)
        
        # Button bar for editor
        button_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=5)
        editor_box.pack_start(button_box, False, False, 0)
        
        # Open File button
        open_button = Gtk.Button(label="Open File")
        open_button.connect("clicked", self.on_open_clicked)
        button_box.pack_start(open_button, False, False, 0)
        
        # Load Input button (new)
        load_input_button = Gtk.Button(label="Load Input")
        load_input_button.connect("clicked", self.on_load_input_clicked)
        button_box.pack_start(load_input_button, False, False, 0)
        
        # Save button
        save_button = Gtk.Button(label="Save")
        save_button.connect("clicked", self.on_save_clicked)
        button_box.pack_start(save_button, False, False, 0)
        
        # Compile button with styling
        compile_button = Gtk.Button(label="Compile")
        compile_button.connect("clicked", self.on_compile_clicked)
        compile_button.get_style_context().add_class("suggested-action")
        button_box.pack_end(compile_button, False, False, 0)
        
        # ===== Output Section =====
        output_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=5)
        
        # Output label
        output_label = Gtk.Label()
        output_label.set_markup("<b>Compilation Results</b>")
        output_label.set_halign(Gtk.Align.START)
        output_box.pack_start(output_label, False, False, 0)
        
        # Output notebook (tabs)
        self.notebook = Gtk.Notebook()
        output_box.pack_start(self.notebook, True, True, 0)
        
        # Create output tabs
        self.create_output_tabs()
        
        # Add both sections to paned container
        paned.pack1(editor_box, True, False)  # Editor gets focus when window is resized
        paned.pack2(output_box, True, False)
        paned.set_position(350)  # Initial position of divider
        
        # Status bar
        self.statusbar = Gtk.Statusbar()
        self.status_context_id = self.statusbar.get_context_id("main")
        main_box.pack_start(self.statusbar, False, False, 0)
        self.statusbar.push(self.status_context_id, "Ready")
    
    def create_source_view(self):
        # Create a scrolled window for the source view
        self.source_scroll = Gtk.ScrolledWindow()
        self.source_scroll.set_policy(Gtk.PolicyType.AUTOMATIC, Gtk.PolicyType.AUTOMATIC)
        
        # Create a source language manager and get plain text language
        lang_manager = GtkSource.LanguageManager()
        lang = lang_manager.get_language("c")  # Using C syntax highlighting (can be changed)
        
        # Create source buffer with language
        self.source_buffer = GtkSource.Buffer()
        if lang:
            self.source_buffer.set_language(lang)
        self.source_buffer.set_highlight_syntax(True)
        
        # Create source view with the buffer
        self.source_view = GtkSource.View(buffer=self.source_buffer)
        self.source_view.set_show_line_numbers(True)
        self.source_view.set_auto_indent(True)
        self.source_view.set_tab_width(4)
        self.source_view.set_monospace(True)
        
        # Set font
        font_desc = Pango.FontDescription("monospace 11")
        self.source_view.override_font(font_desc)
        
        # Add source view to scrolled window
        self.source_scroll.add(self.source_view)
    
    def create_output_tabs(self):
        # Quadrables tab (CSV only)
        self.quadrables_scroll = Gtk.ScrolledWindow()
        self.quadrables_scroll.set_policy(Gtk.PolicyType.AUTOMATIC, Gtk.PolicyType.AUTOMATIC)
        self.quadrables_table = Gtk.TreeView()
        self.quadrables_scroll.add(self.quadrables_table)
        
        # Symbol table tab (CSV only)
        self.symbol_table_scroll = Gtk.ScrolledWindow()
        self.symbol_table_scroll.set_policy(Gtk.PolicyType.AUTOMATIC, Gtk.PolicyType.AUTOMATIC)
        self.symbol_table = Gtk.TreeView()
        self.symbol_table_scroll.add(self.symbol_table)
        
        # Error tab (stays as text view)
        self.error_scroll = Gtk.ScrolledWindow()
        self.error_scroll.set_policy(Gtk.PolicyType.AUTOMATIC, Gtk.PolicyType.AUTOMATIC)
        self.error_view = Gtk.TextView()
        self.error_view.set_editable(False)
        self.error_view.set_monospace(True)
        self.error_scroll.add(self.error_view)
        self.error_buffer = self.error_view.get_buffer()
        
        # Add tabs to notebook
        self.notebook.append_page(self.quadrables_scroll, Gtk.Label(label="Quadrables"))
        self.notebook.append_page(self.symbol_table_scroll, Gtk.Label(label="Symbol Table"))
        self.notebook.append_page(self.error_scroll, Gtk.Label(label="Errors"))
    
    def load_csv_into_treeview(self, treeview, filename):
        # Clear existing columns
        for column in treeview.get_columns():
            treeview.remove_column(column)
        
        try:
            with open(filename, 'r', newline='') as csvfile:
                reader = csv.reader(csvfile)
                headers = next(reader, [])  # Get headers (first row)
                
                if not headers:
                    return False
                
                # Create a list store with appropriate types (all strings for simplicity)
                list_store_types = [str] * len(headers)
                list_store = Gtk.ListStore(*list_store_types)
                
                # Add rows to list store
                for row in reader:
                    # Ensure row has same length as headers (pad if necessary)
                    padded_row = row + [''] * (len(headers) - len(row))
                    list_store.append(padded_row[:len(headers)])
                
                # Set model for tree view
                treeview.set_model(list_store)
                
                # Add columns
                for i, header in enumerate(headers):
                    renderer = Gtk.CellRendererText()
                    column = Gtk.TreeViewColumn(header, renderer, text=i)
                    column.set_resizable(True)
                    column.set_sort_column_id(i)
                    treeview.append_column(column)
                
                return True
        except (csv.Error, IOError) as e:
            print(f"Error loading CSV: {str(e)}")
            return False
    
    def load_file(self, filename):
        try:
            with open(filename, 'r') as f:
                content = f.read()
                self.source_buffer.set_text(content)
                self.statusbar.push(self.status_context_id, f"Loaded: {filename}")
        except Exception as e:
            self.show_error_dialog(f"Error loading file: {str(e)}")
    
    def on_open_clicked(self, button):
        dialog = Gtk.FileChooserDialog(
            title="Please choose a file",
            parent=self,
            action=Gtk.FileChooserAction.OPEN
        )
        dialog.add_buttons(
            Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
            Gtk.STOCK_OPEN, Gtk.ResponseType.OK
        )
        
        # Add filters for text files
        filter_text = Gtk.FileFilter()
        filter_text.set_name("Text files")
        filter_text.add_mime_type("text/plain")
        dialog.add_filter(filter_text)
        
        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            self.load_file(dialog.get_filename())
        
        dialog.destroy()
    
    def on_load_input_clicked(self, button):
        dialog = Gtk.FileChooserDialog(
            title="Select input file to load",
            parent=self,
            action=Gtk.FileChooserAction.OPEN
        )
        dialog.add_buttons(
            Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
            "Load as Input", Gtk.ResponseType.OK
        )
        
        # Add filters for text files
        filter_text = Gtk.FileFilter()
        filter_text.set_name("Text files")
        filter_text.add_mime_type("text/plain")
        dialog.add_filter(filter_text)
        
        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            try:
                selected_file = dialog.get_filename()
                # Load the file content
                with open(selected_file, 'r') as f:
                    content = f.read()
                
                # Ensure data directory exists
                os.makedirs("./data", exist_ok=True)
                
                # Save to input.txt
                with open("./data/input.txt", 'w') as f:
                    f.write(content)
                
                # Load the content to editor
                self.source_buffer.set_text(content)
                self.statusbar.push(self.status_context_id, f"Loaded '{selected_file}' as input.txt")
            except Exception as e:
                self.show_error_dialog(f"Error loading input: {str(e)}")
        
        dialog.destroy()
    
    def on_save_clicked(self, button):
        try:
            start_iter = self.source_buffer.get_start_iter()
            end_iter = self.source_buffer.get_end_iter()
            text = self.source_buffer.get_text(start_iter, end_iter, False)
            
            # Ensure data directory exists
            os.makedirs("./data", exist_ok=True)
            
            with open("./data/input.txt", 'w') as f:
                f.write(text)
            
            self.statusbar.push(self.status_context_id, "Saved to input.txt")
        except Exception as e:
            self.show_error_dialog(f"Error saving file: {str(e)}")
    
    def on_compile_clicked(self, button):
        self.on_save_clicked(None)

        if not os.path.exists("./bin/calc"):
            self.show_error_dialog("Compiler executable 'calc' not found!")
            return

        try:
            if not os.access("./bin/calc", os.X_OK):
                os.chmod("./bin/calc", 0o755)

            # Ensure logs directory exists
            os.makedirs("./logs", exist_ok=True)

            print("[DEBUG] Running calc...")
            process = subprocess.Popen(["./bin/calc", "./data/input.txt"],
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE)
            stdout, stderr = process.communicate(timeout=5)

            self.load_output_files()
            self.statusbar.push(self.status_context_id, "Compilation complete")

        except subprocess.TimeoutExpired:
            process.kill()
            self.show_error_dialog("Compilation timed out after 5 seconds")
        except Exception as e:
            self.show_error_dialog(f"Error during compilation: {str(e)}")

    def load_output_files(self):
        # Reset table views
        for column in self.quadrables_table.get_columns():
            self.quadrables_table.remove_column(column)
        
        for column in self.symbol_table.get_columns():
            self.symbol_table.remove_column(column)
        
        # Load quadrables.csv
        if os.path.exists("./logs/quadrables.csv"):
            self.load_csv_into_treeview(self.quadrables_table, "./logs/quadrables.csv")
        else:
            # Create empty model with message
            list_store = Gtk.ListStore(str)
            list_store.append(["No quadrables CSV file generated"])
            self.quadrables_table.set_model(list_store)
            
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn("Message", renderer, text=0)
            self.quadrables_table.append_column(column)
        
        # Load symbol table CSV
        if os.path.exists("./logs/output_symbol_table.csv"):
            self.load_csv_into_treeview(self.symbol_table, "./logs/output_symbol_table.csv")
        else:
            # Create empty model with message
            list_store = Gtk.ListStore(str)
            list_store.append(["No symbol table CSV file generated"])
            self.symbol_table.set_model(list_store)
            
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn("Message", renderer, text=0)
            self.symbol_table.append_column(column)
        
        # Load error_file.txt
        has_errors = False
        if os.path.exists("./logs/error_file.txt"):
            with open("./logs/error_file.txt", 'r') as f:
                content = f.read()
                self.error_buffer.set_text(content)
                if content.strip():
                    has_errors = True
        else:
            self.error_buffer.set_text("(No error file generated)")
        
        # Switch to error tab if there are errors
        if has_errors:
            self.notebook.set_current_page(2)  # Switch to error tab (index 2)
            # Highlight the error text with a red background
            tag_table = self.error_buffer.get_tag_table()
            # Check if tag already exists
            error_tag = tag_table.lookup("error_background")
            if not error_tag:
                error_tag = Gtk.TextTag.new("error_background")
                error_tag.set_property("background", "#ffecec" if not self.dark_mode else "#552222")
                tag_table.add(error_tag)
            
            start = self.error_buffer.get_start_iter()
            end = self.error_buffer.get_end_iter()
            self.error_buffer.apply_tag_by_name("error_background", start, end)
    
    def show_error_dialog(self, message):
        dialog = Gtk.MessageDialog(
            transient_for=self,
            flags=0,
            message_type=Gtk.MessageType.ERROR,
            buttons=Gtk.ButtonsType.OK,
            text="Error",
        )
        dialog.format_secondary_text(message)
        dialog.run()
        dialog.destroy()
    
    def on_theme_switched(self, switch, gparam):
        self.dark_mode = switch.get_active()
        self.apply_theme()
    
    def apply_theme(self):
        # Get Gtk settings
        settings = Gtk.Settings.get_default()
        
        if self.dark_mode:
            # Set dark theme
            settings.set_property("gtk-application-prefer-dark-theme", True)
            
            # Apply dark mode styles
            style_provider = Gtk.CssProvider()
            css = """
            .view, textview text {
                background-color: #2d2d2d;
                color: #e0e0e0;
            }
            treeview {
                background-color: #2d2d2d;
                color: #e0e0e0;
            }
            treeview:selected {
                background-color: #4a90d9;
            }
            .header {
                background-color: #353535;
            }
            notebook tab {
                background-color: #353535;
                color: #e0e0e0;
            }
            notebook tab:checked {
                background-color: #4a4a4a;
                color: #ffffff;
            }
            """
            style_provider.load_from_data(css.encode())
        else:
            # Set light theme
            settings.set_property("gtk-application-prefer-dark-theme", False)
            
            # Apply light mode styles
            style_provider = Gtk.CssProvider()
            css = """
            .view, textview text {
                background-color: #ffffff;
                color: #000000;
            }
            treeview {
                background-color: #ffffff;
                color: #000000;
            }
            treeview:selected {
                background-color: #4a90d9;
                color: #ffffff;
            }
            .header {
                background-color: #f5f5f5;
            }
            notebook tab {
                background-color: #f0f0f0;
                color: #333333;
            }
            notebook tab:checked {
                background-color: #e0e0e0;
                color: #000000;
            }
            """
            style_provider.load_from_data(css.encode())
            
        # Apply the CSS provider to the screen
        screen = Gdk.Screen.get_default()
        Gtk.StyleContext.add_provider_for_screen(
            screen,
            style_provider,
            Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION
        )
        
        # Update error highlighting color if needed
        tag_table = self.error_buffer.get_tag_table()
        error_tag = tag_table.lookup("error_background")
        if error_tag:
            error_tag.set_property("background", "#ffecec" if not self.dark_mode else "#552222")
        
        # Force redraw
        self.queue_draw()

if __name__ == "__main__":
    app = ClacCompilerApp()
    app.run(None)
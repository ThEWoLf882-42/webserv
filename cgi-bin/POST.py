#!/usr/bin/env python3

import os
import cgi
import cgitb

cgitb.enable()  # Enable detailed error reporting

def main():
    print("Content-Type: text/html\r\n")  # Headers must end with a blank line

    form = cgi.FieldStorage()

    if os.environ['REQUEST_METHOD'] == 'POST':
        print("<html><body>")
        print("<h2>POST Request Received</h2>")
        print("<ul>")
        
        for field in form.keys():
            field_item = form[field]
            if field_item.filename:
                # It's a file upload
                file_data = field_item.file.read()
                with open(f"/tmp/{field_item.filename}", "wb") as f:
                    f.write(file_data)
                print(f"<li>Uploaded file: {field_item.filename}</li>")
            else:
                # Regular form field
                print(f"<li>{field}: {form.getvalue(field)}</li>")
        
        print("</ul>")
        print("</body></html>")
    else:
        print("<html><body>")
        print("<h2>Invalid Request</h2>")
        print("</body></html>")

if __name__ == "__main__":
    main()

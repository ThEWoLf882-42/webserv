import os
import cgi
import cgitb
import urllib.parse

cgitb.enable()

UPLOAD_DIR = os.environ.get('UPLOAD_DIR', './upload')

# Ensure the upload directory exists
if not os.path.exists(UPLOAD_DIR):
    os.makedirs(UPLOAD_DIR)

def handle_post():
    print("Content-Type: text/html\r\n\r\n")

    form = cgi.FieldStorage()
    if form.list is None:
        print("<html><body><h2>No form data received</h2></body></html>")
        return

    print("<html><body>")
    print("<h2>POST Request Received</h2>")
    print("<ul>")
    
    for field in form.keys():
        field_item = form[field]
        if field_item.filename:
            # It's a file upload
            file_data = field_item.file.read()
            file_path = os.path.join(UPLOAD_DIR, field_item.filename)
            with open(file_path, "wb") as f:
                f.write(file_data)
            print(f"<li>Uploaded file: {field_item.filename} to {file_path}</li>")
        else:
            # Regular form field
            print(f"<li>{field}: {form.getvalue(field)}</li>")
    
    print("</ul>")
    print("</body></html>")

def handle_delete():
    print("Content-Type: text/html\r\n\r\n")
    query_string = os.environ.get('QUERY_STRING', '')

    if query_string:
        params = urllib.parse.parse_qs(query_string)
        resource_id = params.get('id', [None])[0]
        if resource_id:
            resource_path = os.path.join(UPLOAD_DIR, resource_id)
            try:
                if os.path.exists(resource_path):
                    os.remove(resource_path)
                    print(f"<html><body><h2>Resource {resource_id} deleted successfully.</h2></body></html>")
                else:
                    print(f"<html><body><h2>Resource {resource_id} not found.</h2></body></html>")
            except Exception as e:
                print(f"<html><body><h2>Error deleting resource: {e}</h2></body></html>")
        else:
            print("<html><body><h2>Resource ID not specified.</h2></body></html>")
    else:
        print("<html><body><h2>No query string provided.</h2></body></html>")

def handle_get():
    print("Content-Type: text/html\r\n\r\n")
    query_string = os.environ.get('QUERY_STRING', '')

    if query_string:
        params = urllib.parse.parse_qs(query_string)
        print("<html><body>")
        print("<h2>GET Request Received</h2>")
        print("<ul>")
        for key, values in params.items():
            for value in values:
                print(f"<li>{key}: {value}</li>")
        print("</ul>")
        print("</body></html>")
    else:
        print("<html><body><h2>No query string provided.</h2></body></html>")

def handle_put():
    print("Content-Type: text/html\r\n\r\n")

    form = cgi.FieldStorage()
    if form.list is None:
        print("<html><body><h2>No form data received</h2></body></html>")
        return

    print("<html><body>")
    print("<h2>PUT Request Received</h2>")
    print("<ul>")
    
    for field in form.keys():
        field_item = form[field]
        if field_item.filename:
            file_data = field_item.file.read()
            file_path = os.path.join(UPLOAD_DIR, field_item.filename)
            with open(file_path, "wb") as f:
                f.write(file_data)
            print(f"<li>Uploaded file: {field_item.filename} to {file_path}</li>")
        else:
            print(f"<li>{field}: {form.getvalue(field)}</li>")
    
    print("</ul>")
    print("</body></html>")

def main():
    request_method = os.environ.get('REQUEST_METHOD', '').upper()
    if request_method == 'POST':
        handle_post()
    elif request_method == 'DELETE':
        handle_delete()
    elif request_method == 'GET':
        handle_get()
    elif request_method == 'PUT':
        handle_put()
    else:
        print("Content-Type: text/html\r\n\r\n")
        print("<html><body>")
        print(f"<h2>Invalid Request Method: {request_method}</h2>")
        print("</body></html>")

if __name__ == "__main__":
    main()

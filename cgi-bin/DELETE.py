#!/usr/bin/env python3

import os
import cgi
import cgitb
import urllib.parse

cgitb.enable()  # Enable detailed error reporting

def handle_delete():
    print("Content-Type: text/html\r\n")  # Headers must end with a blank line
    query_string = os.environ.get('QUERY_STRING', '')

    if query_string:
        params = urllib.parse.parse_qs(query_string)
        resource_id = params.get('id', [None])[0]
        if resource_id:
            # Simulate resource deletion
            # Here you can add your logic to delete the resource, for example, delete a file
            resource_path = f"/path/to/resources/{resource_id}"
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

def main():
    request_method = os.environ['REQUEST_METHOD']
    if request_method == 'DELETE':
        handle_delete()
    else:
        print("Content-Type: text/html\r\n")  # Headers must end with a blank line
        print("<html><body>")
        print(f"<h2>Invalid Request Method: {request_method}</h2>")
        print("</body></html>")

if __name__ == "__main__":
    main()

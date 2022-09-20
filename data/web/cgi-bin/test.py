#!/usr/bin/env python3

import cgi
import html

form = cgi.FieldStorage()
text1 = form.getfirst("test", "not set")
text2 = form.getfirst("test2", "not set")
text1 = html.escape(text1)
text2 = html.escape(text2)

#print("Status: 200 OK\r")
print("Content-Type: text/html; charset=utf-8\r\n\r")
print("First name: ", text1)
print("<br>")
print("Second name: ", text2)
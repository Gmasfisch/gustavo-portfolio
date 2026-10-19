import os
from urllib.parse import parse_qs

q = parse_qs(os.environ.get("QUERY_STRING", ""))
name = q.get("name", ["world"])[0]

print("Content-Type: text/plain")
print()
print("hello " + name)

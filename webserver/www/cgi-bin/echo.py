#!/usr/bin/env python3
import os
import sys

body = sys.stdin.read()

print("Content-Type: text/plain")
print()
print("method:", os.environ.get("REQUEST_METHOD"))
print("received:", body)

#!/bin/bash

H=localhost:8080
S=localhost:9090
ok=0
fail=0

#same as curl -s -m 20 -o /dev/null -w  "%{return code from curl}" "H or S variables above" 
code() { curl -s -m 20 -o /dev/null -w "%{http_code}" "$@"; }

check() {   # expected name
    if [ "$2" = "$3" ]; then
        echo "  OK    $1"; ok=$((ok + 1))
    else
        echo "  FAIL  $1 (expected $2, received $3)"; fail=$((fail + 1))
    fi
}

contains() {   # expected_name name_received
    if [[ "$3" == *"$2"* ]]; then
        echo "  OK    $1"; ok=$((ok + 1))
    else
        echo "  FAIL  $1 (doesnt have '$2')"; fail=$((fail + 1))
    fi
}

echo "== Archivos estaticos y config =="
check "GET /"                          200 "$(code $H/)"
check "GET /doesntexists"                  404 "$(code $H/doesntexists)"
check "GET /old (redirect)"            301 "$(code $H/old)"
check "GET /images/ (autoindex)"       200 "$(code $H/images/)"
check "GET /images (with slash)"        200 "$(code $H/images)"
check "GET /cgi-bin/ (dir without index)"  403 "$(code $H/cgi-bin/)"
check "GET /../ (path traversal)"      403 "$(code --path-as-is $H/../)"
check "segundo server: 404"            404 "$(code $S/doesntexists)"

echo "== Metodos =="
check "POST / (only GET)"              405 "$(code -X POST --data x $H/)"
check "DELETE / (only GET)"            405 "$(code -X DELETE $H/)"
check "DELETE /uploads/ (directorio)"  403 "$(code -X DELETE $H/uploads/)"

echo "== Upload y DELETE =="
echo "testing content" > /tmp/webserv_test.txt
check "POST upload multipart"                 201 "$(code -F file=@/tmp/webserv_test.txt $H/uploads)"
check "POST with custom filename"             201 "$(code -F "file=@/tmp/webserv_test.txt;filename=anothername.txt" $H/uploads)"
check "GET file with custom filename"         200 "$(code $H/uploads/anothername.txt)"
check "GET file uploaded"                     200 "$(code $H/uploads/webserv_test.txt)"
check "DELETE file uploaded"                  204 "$(code -X DELETE $H/uploads/webserv_test.txt)"
check "GET deleted file"                      404 "$(code $H/uploads/webserv_test.txt)"
check "DELETE something that doesnt exists"   404 "$(code -X DELETE $H/uploads/webserv_test.txt)"
check "DELETE file with custom filename"      204 "$(code -X DELETE $H/uploads/anothername.txt)"
#secutiy: check that you cannot upload a file outside the uploads directory
check "POST upload outside uploads dir" 201 "$(code -F "file=@/tmp/webserv_test.txt;filename=../outside.txt" $H/uploads)"
check "GET file outside uploads dir" 404 "$(code $H/outside.txt)"
check "GET file inside uploads dir" 200 "$(code $H/uploads/outside.txt)"
check "DELETE file outside uploads dir" 405 "$(code -X DELETE $H/outside.txt)"
check "DELETE file inside uploads dir" 204 "$(code -X DELETE $H/uploads/outside.txt)"
rm -f /tmp/webserv_test.txt

echo "== CGI =="
check "CGI .py inexistente"            404 "$(code $H/cgi-bin/noexiste.py)"
contains "CGI .py GET with query" "hello gustavo" "$(curl -s -m 20 "$H/cgi-bin/hello.py?name=gustavo")"
contains "CGI .py POST with body" "received: name=gustavo" "$(curl -s -m 20 --data 'name=gustavo' $H/cgi-bin/echo.py)"
contains "CGI .sh (second language)" "method GET" "$(curl -s -m 20 $H/cgi-bin/salute.sh)"

echo "== Request mal formada =="
if command -v nc > /dev/null; then
    contains "request basura -> 400" "400" "$(printf 'BASURA\r\n\r\n' | nc -w 2 localhost 8080 | head -1)"
else
    echo "  SKIP  request basura (falta nc)"
fi

if [ "$1" = "--slow" ]; then
    echo "== Timeout del CGI (espera ~15 s) =="
    check "CGI que tarda -> 504"       504 "$(curl -s -m 30 -o /dev/null -w '%{http_code}' $H/cgi-bin/sleep.sh)"
fi

echo
echo "Resultado: $ok OK, $fail FAIL"
[ "$fail" -eq 0 ]

# to test during eval
# cat /proc/$(pgrep -f "sh sleep.sh")/environ | tr '\0' '\n'  to check env variables of the script during the sleep.sh script
# curl -i localhost:8080 see complete answer, with status line, headers and body 
# curl -X POST --data-binary @README.md localhost:8080/cgi-bin/echo.py Send a file as a body, @ means read from this file. 
# curl -F "file=@whatever.whatever" localhost:8080 Upload multipart as a form. ;filename=... changes the name =
# printf '...' | nc localhost 8080 Send Crude Data (malformed request) 
# pgrep -f "patrón" Pid de un proceso buscando en su línea de comando
# completa.
# pgrep -af patrón Lo mismo, mostrando la línea completa de cada uno.
# ls -l /proc/PID/fd La tabla de fds de un proceso.
# cat /proc/PID/environ | tr '\0' '\n' Sus variables de entorno.
# ls -l /proc/PID/cwd Su directorio actual (en el CGI, debería ser cgi-bin por el
# chdir).
# echo $? Código de salida del último comando. 141 = SIGPIPE, 137 =
# SIGKILL (por ejemplo, el kernel sin memoria).
# kill $(pgrep webserv) Matar solo al server. Ctrl+C mata a todo el grupo, incluidos
# los CGI.
# head -c N /dev/zero > f Crear un archivo de N bytes de ceros para pruebas.
# siege -b -q -c 25 -t 30S URL Prueba de carga del subject.
# top CPU y memoria (RES) del server durante las pruebas.
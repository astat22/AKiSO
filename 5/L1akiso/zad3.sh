ping google.com -c 400 | cut -d ' ' -f7 | cat >  connect &
ps -ef | grep 'ping'
ps -ef | grep 'cut'
ps -ef | grep 'cat'


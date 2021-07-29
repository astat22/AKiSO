for i in ./*; do mv -f "$i" "$(echo "$i" | tr '[:upper:]' '[:lower:]')"; done

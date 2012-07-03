#!/bin/sh

case "$1" in
  start)
   /usr/bin/lucifer &
   ;;
  stop)
   killall -9 lucifer
   ;;
  *)
   echo "Usage: $0 start|stop" >&2
   ;;
esac

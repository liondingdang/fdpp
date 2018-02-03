(case "$1" in
    1)
	sed "s/^\( *\)\(.*[ (),]\)$2(\([^)]\+\))\(.*\)$/\1$3 (@\3@, \3); \2$4 (@\3@)\4/g"
	;;
    2)
	sed "s/^\( *\)\(.*[ (),]\)$2(\([^)]\+\))\(.*\)$/\1\{ $3 (@\3@, \3); \2$4 (@\3@)\4 \}/g"
	;;
    3)
	sed "s/^\( *\)\(.*[ (),]\)$2(\([^)]\+\))\(.*\)$/\1$3 (__sss, \3); \2$4 (__sss)\4/g"
	;;
    4)
	sed "s/^\( *\)\(.*[ (),]\)$2(\([^)]\+\))\(.*\)$/\1\{ $3 (__sss, \3); \2$4 (__sss)\4 \}/g"
	;;
esac) | awk '{
    if (match($0, "(.*)@(.*)@(.*)@(.*)@(.*)", a) == 0) {
      print
    } else {
      gsub("\\.", "_" , a[2])
      gsub("\\.", "_" , a[4])
      print (a[1] a[2] a[3] a[4] a[5])
    }
}'

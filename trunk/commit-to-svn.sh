#!/bin/bash

cd rtems

svn st | grep ^! | sed -e 's/!\s*/\svn remove /' -e 's/$/ \&\&/' | sed ':a;N;$!ba;s/\n/ /g' | sed -e 's/\&\&\s*$//' | bash

svn st | grep ^? | sed -e 's/?\s*/\svn add /' -e 's/$/ \&\&/' | sed ':a;N;$!ba;s/\n/ /g' | sed -e 's/\&\&\s*$//' | bash

svn commit -m "update to CVS head" --username gedare@gwmail.gwu.edu

cd ..

echo "svn now updated to head"


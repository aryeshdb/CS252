#!/bin/bash
echo "<!DOCTYPE html>
<html>
<body>

<h2>HTML Image</h2>" > index.html

for filename in images/*.jpg; do
	echo "<center><img src=\""$filename"\" style=\"width:300px;height:300px;\" alt=\"Italian Trulli\" border=\"5\" ><center><br>" >> index.html
done

echo "</body>
</html>" >>index.html

firefox index.html
rm images/*.jpg

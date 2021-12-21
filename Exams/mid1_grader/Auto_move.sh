filelist=`ls | grep -v Auto`
for file in $filelist
do
	if [ ! -f ${file}/Problem1.m ]; then
		echo $file
		cd $file
		my_path=`find . -name Problem1.m | awk -F '/' '{print $2}'`
		cp ${my_path}/Prob*.m .
		cd ..
	fi
done

#!/bin/bash 

#变量定义，等号两侧不能有空格
#变量类型
#普通变量
#环境变量 export VAR=...
#局部变量 local VAR=...
#位置变量
#特殊变量

#参数个数
echo $#

#脚本名
echo $0 

#所有参数
echo $*

#进程号
echo $$

#上条命令返回值
echo $?


STR="Hello world"
echo $STR
echo ${STR}

#引号
#''不解析变量
echo '$STR'
#""解析变量
echo "$STR"
#``执行并引用一个命令的执行结果，相当于 $()
echo `date`
echo $(date)
CMD=date
echo $($CMD)
echo `$CMD`
echo `echo $CMD`


#循环语句
for ((i=0; i<10;i++))
do
	test $i
done

for i in 0 1 2 3 4 5 6 7 8 9
do
	test $i
done

for i in {0..9}
do
	echo $i
done

for i in {0..9..2}
do
	echo $i
done

echo "for"
for i in `ls`
do
	test $i
done

echo "while"
num=0
while [ $num -lt 10 ]
do
	echo $num
	let num=$num+1
done

#continue
#break

#条件测试
#test
#[ EXPR ] :注意中括号和表达式之间的空格
# -lt -gt -ge -le -eq -ne
num1=0
num2=10
#while test $num1 -lt $num2
while [ $num1 -lt $num2 ]
do
	echo $num1, $num2
	let num1=$num1+1
	let num2=$num2-1
done

#条件语句
if [ 11 -lt 2 ] ;then
	echo "little"
fi

if
then
else
fi

if then
elif then
elif then
else 
fi




















read VAR
echo "VAR is $VAR"

expr $VAR - 5

test "Hello"="HelloWorld"

test $VAR -eq 10

test -d ./Android

exec ./othershell.sh

exit

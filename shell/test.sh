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

#if
#then
#else
#fi

#if then
#elif then
#elif then
#else 
#fi

#case
#case 变量引用 in
#PATTERN1)
#分支1
#;;
#PATTERN2)
#分支2
#;;
#...
#*)
#分支n
#;;
#esac

echo "case cause"
num=10
case $num in
	1)
		echo 1;;
	2)
		echo 2;;
	10)
		echo 10;;
esac

#let varName=算术表达式
#
#varName=$[算术表达式]
#
#varName=$((算术表达式))
#
#varName=`expr $num1 + $num2`

varName=$((100+10))
echo ${varName}

#运算符号两侧要有空格
varName=`expr 200 - 10`
echo ${varName}

varName=$[$varName-10]
echo ${varName}

#逻辑运算符
#-a -o !
#if [ condA -a condB ]
#if [ condA ] && [ condB ]
#if [[ condA && condB ]]

#自定义函数
#函数的返回值，只能是数字
function F() {
	pass
}

#read
#表示输入时的提示字符串：
read -p "Enter your name:" VAR_NAME

#declare
# -r 只读
# -i 整数: 某些算术计算允许在被声明为整数的变量中完成，而不需要特别使用expr或let来完成
# -a 数组
declare -i num5
num5=$num+10
echo $num5

#字符串长度
#${#VAR_NAME}
echo ${#num5}

#字符串截取
#${variable:offset:length}或者${variable:offset}

#尾部指定个数
#${variable: -length}：注意冒号后面有空格

#大小写转换
#${variable^^} 小写转大写
#${variable,,} 大写换小写

name=Alice
echo ${name^^}
echo ${name,,}


#数组
#declare -a var_name
#${ARRAY[index]}：查看数组指定角标的元素
#${ARRAY}：查看数组的第一个元素
#${ARRAY[*]}或者${ARRAY[@]}：查看数组的所有元素

#获取数组内元素的长度
#${#ARRAY[0]}
#${#ARRAY[0]}表示获取数组中的第一个元素的长度，等于${#ARRAY}

#从数组中获取某一片段之内的元素（操作类似于字符串操作）
#${ARRAY[@]:offset:length}
#offset：偏移的元素个数
#length：取出的元素的个数
#${ARRAY[@]:offset:length}：取出偏移量后的指定个数的元素
#${ARRAY[@]:offset}：取出数组中偏移量后的所有元素

#数组删除元素
#unset ARRAY[index]

#date
#格式化输出 +%Y-%m-%d
#格式%s表示自1970-01-01 00:00:00以来的秒数
#指定时间输出  --date='2009-01-01 11:11:11'
#指定时间输出  --date='3 days ago' （3天之前，3天之后可以用-3）

#后台运行
#&
#这样的话虽然可以在后台运行，但是当用户注销(logout)或者网络断开时,终端会收到Linux HUP信号(hangup)信号从而关闭其所有子进程

#nohup
#不挂断的运行命令，忽略所有挂断(hangup)信号



























read VAR
echo "VAR is $VAR"

expr $VAR - 5

test "Hello"="HelloWorld"

test $VAR -eq 10

test -d ./Android

exec ./othershell.sh

exit

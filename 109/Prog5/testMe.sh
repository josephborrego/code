#!/bin/bash

echo "This generates test cases worth 60 points of the assignment."

echo "Provide an executable ./prog5 that handles the following command line arguments"
echo "./prog5 1 <file1> <file2>: readFile(file1), saveToFile(file2)"
echo "./prog5 2 <file1> <file2> <file3>: readFile(file1), appendFromFile(file2), saveToFile(file3)"
echo "./prog5 3 <file1> <file2> <file3>: readFile(file1), readFile(file2), for each name in file2, removeByName(file1, name), saveToFile(file3) (save file1)"
echo ""

if [ ! -f ./prog5 ]
then
	echo "Executable does not exist"
	exit 2;
fi

echo "Generating test cases testInput.0 ... testInput.9"
~jloew/CSE109/p5student/generator 10 1 > testInput.0
~jloew/CSE109/p5student/generator 10 5 > testInput.1
~jloew/CSE109/p5student/generator 10 15 > testInput.2
~jloew/CSE109/p5student/generator 100 1 > testInput.3
~jloew/CSE109/p5student/generator 100 5 > testInput.4
~jloew/CSE109/p5student/generator 100 15 > testInput.5
~jloew/CSE109/p5student/generator 500 2 > testInput.6
~jloew/CSE109/p5student/generator 500 6 > testInput.7
~jloew/CSE109/p5student/generator 500 16 > testInput.8
~jloew/CSE109/p5student/generator 1000 25 > testInput.9

#echo "Generating solutions for 'read in testInput write out to testOne'"
#echo "You should be able to read in testInput.# and save it as testOne.#"
for i in `seq 0 9`;
do
	~jloew/CSE109/p5student/answer 1 testInput.$i testOne.$i
	./prog5 1 testInput.$i studentOne.$i
	diff testOne.$i studentOne.$i
	value="$?"
	if [ "$value" -ne "0" ]
	then
		rm studentOne.* 2> /dev/null
		echo "Failed test set 1, case $i"
		exit 3;
	fi
done

#echo "Generating solutions for 'read in two testInputs and write out to testTwo'"
#echo "You should be able to read in testInput.# and use appendFromFile to read in testInput.# and write out to testTwo.##"
for i in `seq 0 9`;
do
	for j in `seq 0 9`;
	do
		~jloew/CSE109/p5student/answer 2 testInput.$i testInput.$j testTwo.$i$j
		./prog5 2 testInput.$i testInput.$j studentTwo.$i$j
		diff testTwo.$i$j studentTwo.$i$j
		value="$?"
		if [ "$value" -ne "0" ]
		then
			rm studentTwo.* 2> /dev/null
			echo "Failed test set 2, case $i$j"
			exit 4;
		fi
	done
done

#echo "Generating solutions for 'read in two testInputs, remove from first, any conflicting names in second, write out the remainder of first to testThree'"
#echo "You should be able to read in testInput.# and testInput.# and write out to testThree.##"
for i in `seq 0 9`;
do
	for j in `seq 0 9`;
	do
		~jloew/CSE109/p5student/answer 3 testInput.$i testInput.$j testThree.$i$j
		./prog5 3 testInput.$i testInput.$j studentThree.$i$j
		diff testThree.$i$j studentThree.$i$j
		value="$?"
		if [ "$value" -ne "0" ]
		then
			rm studentThree.* 2> /dev/null
			echo "Failed test set 3, case $i$j"
			exit 5;
		fi
	done
done



rm studentOne.*
rm studentTwo.*
rm studentThree.*
rm testOne.*
rm testTwo.*
rm testThree.*
rm testInput.*
echo "If nothing else printed, looks good!"

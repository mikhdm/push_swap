#!/usr/bin/env bash

# build push_swap if not
if [ -z "$(ls -al | grep push_swap)" ]; then
	make
fi

FIRES=$1
N=$2

LENGTHS=()
ERRORS=0
SUCCESSES=0

# choose appropriate checker on Linux & MacOS
if [[ $(uname) == "Linux" ]]; then
	CHECKER=./checker_linux
elif [[ $(uname) == "Darwin" ]]; then
	CHECKER=./checker_Mac
fi

# run tests
for i in $(seq 1 $FIRES); do
	ARG=`./gen.py $N`
	printf "Arguments: "
	echo $ARG
	
	# run push swap
	INSTRUCTIONS=`./push_swap $ARG`

	# count operations & run checker
	if [ -z "$INSTRUCTIONS" ]; then
		LEN=`echo -n $INSTRUCTIONS | tr " " "\n" | wc -l | xargs`
		VERDICT=`echo -n $INSTRUCTIONS | tr " " "\n" | $CHECKER $ARG | tr -d "\n"`
	else
		LEN=`echo $INSTRUCTIONS | tr " " "\n" | wc -l | xargs`
		VERDICT=`echo $INSTRUCTIONS | tr " " "\n" | $CHECKER $ARG | tr -d "\n"`
	fi

	# show verdict
	if [[ $VERDICT == "OK" ]]; then
		printf "\e[1;32m%s\e[0m\n" $VERDICT
		SUCCESSES=$((SUCCESSES + 1))
	else
		printf "\e[1;31m%s\e[0m\n" $VERDICT
		ERRORS=$((ERRORS + 1))
	fi
	LENGTHS+=($LEN)
done

# calculate stat
SORTED=`echo "${LENGTHS[*]}" | tr ' ' '\n' | sort`
MIN=`echo $SORTED | tr ' ' '\n' | head -n1`
MAX=`echo $SORTED | tr ' ' '\n' | tail -n1`

printf "\n"
printf "Max ops count: %s\n" $MAX
printf "Min ops count: %s\n" $MIN
printf "Success runs count: %d\n" $SUCCESSES
printf "Wrong runs count: %d\n" $ERRORS

#!/usr/bin/env bash

# build push_swap if not
if [ -z "$(ls -al | grep push_swap)" ]; then
	make bonus
fi

FIRES=$1
N=$2

LENGTHS=()
ERRORS=0
SUCCESSES=0

# choose appropriate checker on Linux & MacOS
CHECKER=./checker

# run tests
for i in $(seq 1 $FIRES); do
	ARG=`./gen.py $N`

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
		SUCCESSES=$((SUCCESSES + 1))
		printf "\e[1;32m+\e[0m"
	else
		ERRORS=$((ERRORS + 1))
		printf "\e[1;31m-\e[0m"
	fi
	LENGTHS+=($LEN)
done

BOOMS=0
BOUND=0
if [[ $N == 100 ]]; then
	BOUND=700
	for len in ${LENGTHS[*]}; do
		if [[ $len -ge 700 ]]; then
			BOOMS=$((BOOMS + 1))
		fi
	done
fi

if [[ $N == 500 ]]; then
	BOUND=5500
	for len in ${LENGTHS[*]}; do
		if [[ $len -ge 5500 ]]; then
			BOOMS=$(($BOOMS + 1))
		fi
	done
fi

# calculate stat

SORTED=`echo "${LENGTHS[*]}" | tr ' ' '\n' | sort -n`
MIN=`echo $SORTED | tr ' ' '\n' | head -n1`
MAX=`echo $SORTED | tr ' ' '\n' | tail -n1`

printf "\n"
printf "Max ops count: %s\n" $MAX
printf "Min ops count: %s\n" $MIN
printf "Success runs count: %d\n" $SUCCESSES
printf "Wrong runs count: %d\n" $ERRORS

if [[ ($N == 100) || ($N == 500) ]]; then
	printf "Over max allowed ops count (N=%d (>= %d)): %d\n" $N $BOUND $BOOMS
fi

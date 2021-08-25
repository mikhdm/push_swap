FIRES=$1
N=$2

LENGTHS=()

for i in $(seq 1 $FIRES); do
	ARG=`./gen.py $N`
	printf "Arguments: "
	echo $ARG
	INSTRUCTIONS=`./push_swap $ARG`
	if [ -z "$INSTRUCTIONS" ]; then
		LEN=`echo -n $INSTRUCTIONS | tr " " "\n" | wc -l | xargs`
		VERDICT=`echo -n $INSTRUCTIONS | tr " " "\n" | ./checker_Mac $ARG | tr -d "\n"`
	else
		LEN=`echo $INSTRUCTIONS | tr " " "\n" | wc -l | xargs`
		VERDICT=`echo $INSTRUCTIONS | tr " " "\n" | ./checker_Mac $ARG | tr -d "\n"`
	fi
	if [[ $VERDICT == "OK" ]]; then
		printf "\e[1;32m%s\e[0m\n" $VERDICT
	else
		printf "\e[1;31m%s\e[0m\n" $VERDICT
	fi
	LENGTHS+=($LEN)
done

SORTED=`echo "${LENGTHS[*]}" | tr ' ' '\n' | sort`
MIN=`echo $SORTED | tr ' ' '\n' | head -n1`
MAX=`echo $SORTED | tr ' ' '\n' | tail -n1`

printf "max ops count: %s\n" $MAX
printf "min ops count: %s\n" $MIN


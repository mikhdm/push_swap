FIRES=$1
N=$2

for i in $(seq 1 $FIRES); do
	ARG=`./gen.py $N`
	printf "Arguments: "
	echo $ARG
	INSTRUCTIONS=`./push_swap $ARG`
	printf "Operations count: "
	if [ -z "$INSTRUCTIONS" ]; then
		echo -n $INSTRUCTIONS | tr " " "\n" | wc -l | xargs
		VERDICT=`echo -n $INSTRUCTIONS | tr " " "\n" | ./checker_Mac $ARG | tr -d "\n"`
	else
		echo $INSTRUCTIONS | tr " " "\n" | wc -l | xargs
		VERDICT=`echo $INSTRUCTIONS | tr " " "\n" | ./checker_Mac $ARG | tr -d "\n"`
	fi
	if [[ $VERDICT == "OK" ]]; then
		printf "\e[1;32m%s\e[0m\n" $VERDICT
	else
		printf "\e[1;31m%s\e[0m\n" $VERDICT
	fi
done


#!/bin/sh

ALTLAS=`lcg-infosites --vo atlas ce|wc -l`
LHCB=`lcg-infosites --vo lhcb ce|wc -l`
ALICE=`lcg-infosites --vo alice ce|wc -l`

printf "%-15s|%15s\n" "VO" "#CEs"


if [ "$ALTLAS" -le "$LHCB" ];
then
        if [ "$ALTLAS" -le "$ALICE" ];
        then
			echo "atlas | $ATLAS"
			echo "alice | $ALICE"
        else
			echo "alice | $ALICE"
			echo "atlas | $ATLAS"
        fi
        echo "lhcb | $LHCB"
else
        if [ "$LHCB" -le "$ALICE" ];
        then
			echo "lhcb | $LHCB"
			echo "alice | $ALICE"
        else
			echo "alice | $ALICE"
			echo "lhcb | $LHCB"
        fi
        echo "atlas | $ATLAS"
fi

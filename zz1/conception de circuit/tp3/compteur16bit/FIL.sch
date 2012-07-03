VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3e"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL e
        SIGNAL XLXN_2
        SIGNAL s
        PORT Input e
        PORT Output s
        BEGIN BLOCKDEF inv
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -32 64 -32 
            LINE N 224 -32 160 -32 
            LINE N 64 -64 128 -32 
            LINE N 128 -32 64 0 
            LINE N 64 0 64 -64 
            CIRCLE N 128 -48 160 -16 
        END BLOCKDEF
        BEGIN BLOCK XLXI_4 inv
            PIN I e
            PIN O XLXN_2
        END BLOCK
        BEGIN BLOCK XLXI_5 inv
            PIN I XLXN_2
            PIN O s
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 1760 1360
        BEGIN BRANCH e
            WIRE 240 400 400 400
        END BRANCH
        IOMARKER 240 400 e R180 28
        INSTANCE XLXI_4 400 432 R0
        BEGIN BRANCH XLXN_2
            WIRE 624 400 656 400
        END BRANCH
        INSTANCE XLXI_5 656 432 R0
        BEGIN BRANCH s
            WIRE 880 400 1040 400
        END BRANCH
        IOMARKER 1040 400 s R0 28
        BEGIN DISPLAY 224 544 TEXT "Ne sert qu'a realiser un fil, pour mettre deux noms differents..."
            FONT 32 "Arial"
        END DISPLAY
    END SHEET
END SCHEMATIC

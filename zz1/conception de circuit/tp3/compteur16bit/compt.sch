VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3e"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL compte(15:0)
        SIGNAL compte(3:0)
        SIGNAL compte(7:4)
        SIGNAL compte(11:8)
        SIGNAL compte(15:12)
        SIGNAL CLK
        SIGNAL SW0
        SIGNAL C(31:0)
        SIGNAL C(14)
        SIGNAL AFF_A
        SIGNAL AFF(7:0)
        SIGNAL XLXN_23
        SIGNAL AFF_B
        SIGNAL AFF_C
        SIGNAL AFF_D
        SIGNAL C(17)
        SIGNAL SW1
        PORT Input CLK
        PORT Input SW0
        PORT Output AFF_A
        PORT Output AFF(7:0)
        PORT Output AFF_B
        PORT Output AFF_C
        PORT Output AFF_D
        PORT Input SW1
        BEGIN BLOCKDEF AFF8SEG
            TIMESTAMP 2010 2 27 11 30 24
            RECTANGLE N 64 -752 560 -64 
            RECTANGLE N 0 -204 64 -180 
            LINE N 64 -192 0 -192 
            LINE N 64 -128 0 -128 
            RECTANGLE N 0 -588 64 -564 
            LINE N 64 -576 0 -576 
            LINE N 64 -512 0 -512 
            RECTANGLE N 0 -460 64 -436 
            LINE N 64 -448 0 -448 
            LINE N 64 -384 0 -384 
            RECTANGLE N 0 -332 64 -308 
            LINE N 64 -320 0 -320 
            LINE N 64 -256 0 -256 
            LINE N 144 -116 516 -204 
            LINE N 148 -596 488 -520 
            BEGIN LINE N 332 -732 332 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 340 -736 372 -736 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 380 -732 380 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 340 -688 372 -688 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 332 -684 332 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 380 -684 380 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 340 -640 372 -640 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 428 -732 428 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 436 -736 468 -736 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 476 -732 476 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 436 -688 468 -688 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 428 -684 428 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 476 -684 476 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 436 -640 468 -640 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 236 -732 236 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 244 -736 276 -736 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 284 -732 284 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 244 -688 276 -688 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 236 -684 236 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 284 -684 284 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 244 -640 276 -640 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 140 -732 140 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 148 -736 180 -736 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 188 -732 188 -696 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 148 -688 180 -688 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 140 -684 140 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 188 -684 188 -648 
                LINECOLOR 255 0 0
            END LINE
            BEGIN LINE N 148 -640 180 -640 
                LINECOLOR 255 0 0
            END LINE
            LINE N 256 -752 256 -816 
            LINE N 160 -752 160 -816 
            LINE N 352 -752 352 -816 
            LINE N 448 -752 448 -816 
            LINE N 320 0 320 -64 
            LINE N 320 -80 336 -64 
            LINE N 304 -64 320 -80 
            LINE N 560 -224 624 -224 
            LINE N 560 -288 624 -288 
            LINE N 560 -352 624 -352 
            LINE N 560 -416 624 -416 
            RECTANGLE N 560 -492 624 -468 
            LINE N 560 -480 624 -480 
        END BLOCKDEF
        BEGIN BLOCKDEF CLOCK
            TIMESTAMP 2008 12 18 12 25 56
            RECTANGLE N 64 -64 320 0 
            LINE N 64 -32 0 -32 
            LINE N 320 -32 384 -32 
            RECTANGLE N 320 -44 384 -20 
        END BLOCKDEF
        BEGIN BLOCKDEF cb16ce
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 384 -192 320 -192 
            RECTANGLE N 320 -268 384 -244 
            LINE N 384 -256 320 -256 
            LINE N 0 -192 64 -192 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 0 -128 64 -128 
            LINE N 0 -32 64 -32 
            LINE N 384 -128 320 -128 
            RECTANGLE N 64 -320 320 -64 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 AFF8SEG
            PIN VD(3:0) compte(15:12)
            PIN Pt_D
            PIN VA(3:0) compte(3:0)
            PIN Pt_A
            PIN VB(3:0) compte(7:4)
            PIN Pt_B
            PIN VC(3:0) compte(11:8)
            PIN Pt_C
            PIN CLK C(14)
            PIN AFF_D AFF_D
            PIN AFF_C AFF_C
            PIN AFF_B AFF_B
            PIN AFF_A AFF_A
            PIN AFF(7:0) AFF(7:0)
            PIN E_VD SW1
            PIN E_VA SW1
            PIN E_VB SW1
            PIN E_VC SW1
        END BLOCK
        BEGIN BLOCK XLXI_2 CLOCK
            PIN CLK CLK
            PIN C_DIV(31:0) C(31:0)
        END BLOCK
        BEGIN BLOCK XLXI_3 cb16ce
            PIN C C(17)
            PIN CE SW0
            PIN CLR
            PIN CEO
            PIN Q(15:0) compte(15:0)
            PIN TC
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        BEGIN INSTANCE XLXI_1 1616 1168 R0
        END INSTANCE
        INSTANCE XLXI_3 560 1040 R0
        BEGIN BRANCH compte(15:0)
            WIRE 944 784 1072 784
        END BRANCH
        BEGIN BRANCH compte(3:0)
            WIRE 1440 592 1616 592
        END BRANCH
        BEGIN BRANCH compte(7:4)
            WIRE 1440 720 1616 720
        END BRANCH
        BEGIN BRANCH compte(11:8)
            WIRE 1440 848 1616 848
        END BRANCH
        BEGIN BRANCH compte(15:12)
            WIRE 1440 976 1616 976
        END BRANCH
        BEGIN INSTANCE XLXI_2 448 336 R0
        END INSTANCE
        BEGIN BRANCH CLK
            WIRE 416 304 448 304
        END BRANCH
        IOMARKER 416 304 CLK R180 28
        BEGIN BRANCH C(31:0)
            WIRE 832 304 1056 304
        END BRANCH
        BEGIN BRANCH C(14)
            WIRE 1936 1168 1936 1280
            WIRE 1936 1280 1952 1280
        END BRANCH
        BEGIN BRANCH AFF_A
            WIRE 2240 752 2272 752
        END BRANCH
        IOMARKER 2272 752 AFF_A R0 28
        BEGIN BRANCH AFF(7:0)
            WIRE 2240 688 2272 688
        END BRANCH
        IOMARKER 2272 688 AFF(7:0) R0 28
        IOMARKER 256 832 SW0 R180 28
        BEGIN BRANCH SW0
            WIRE 256 832 272 832
            WIRE 272 832 496 832
            WIRE 496 832 496 848
            WIRE 496 848 560 848
        END BRANCH
        BEGIN BRANCH AFF_B
            WIRE 2240 816 2272 816
        END BRANCH
        IOMARKER 2272 816 AFF_B R0 28
        BEGIN BRANCH AFF_C
            WIRE 2240 880 2272 880
        END BRANCH
        IOMARKER 2272 880 AFF_C R0 28
        BEGIN BRANCH AFF_D
            WIRE 2240 944 2272 944
        END BRANCH
        IOMARKER 2272 944 AFF_D R0 28
        BEGIN BRANCH C(17)
            WIRE 336 912 560 912
        END BRANCH
        BEGIN BRANCH SW1
            WIRE 1776 304 1776 352
            WIRE 1776 304 1872 304
            WIRE 1872 304 1872 352
            WIRE 1872 304 1920 304
            WIRE 1920 304 1968 304
            WIRE 1968 304 1968 352
            WIRE 1968 304 2064 304
            WIRE 2064 304 2064 352
            WIRE 1920 208 1920 304
        END BRANCH
        IOMARKER 1920 208 SW1 R270 28
    END SHEET
END SCHEMATIC

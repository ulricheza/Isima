VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3e"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL Q(0)
        SIGNAL Q(1)
        SIGNAL XLXN_140
        SIGNAL AFF_D
        SIGNAL AFF_C
        SIGNAL AFF_B
        SIGNAL AFF_A
        SIGNAL XLXN_160
        SIGNAL XLXN_178
        SIGNAL XLXN_179
        SIGNAL XLXN_180
        SIGNAL E_VA
        SIGNAL E_VB
        SIGNAL E_VC
        SIGNAL E_VD
        SIGNAL AFF(7)
        SIGNAL XLXN_237
        SIGNAL V(3:0)
        SIGNAL AFF(6:0)
        SIGNAL AFF(7:0)
        SIGNAL CLK
        SIGNAL XLXN_131
        SIGNAL Pt_D
        SIGNAL Pt_C
        SIGNAL Pt_B
        SIGNAL Pt_A
        SIGNAL XLXN_250
        SIGNAL VA(3:0)
        SIGNAL VB(3:0)
        SIGNAL VC(3:0)
        SIGNAL VD(3:0)
        SIGNAL Q(1:0)
        PORT Output AFF_D
        PORT Output AFF_C
        PORT Output AFF_B
        PORT Output AFF_A
        PORT Input E_VA
        PORT Input E_VB
        PORT Input E_VC
        PORT Input E_VD
        PORT Output AFF(7:0)
        PORT Input CLK
        PORT Input Pt_D
        PORT Input Pt_C
        PORT Input Pt_B
        PORT Input Pt_A
        PORT Input VA(3:0)
        PORT Input VB(3:0)
        PORT Input VC(3:0)
        PORT Input VD(3:0)
        BEGIN BLOCKDEF cb2ce
            TIMESTAMP 2000 1 1 10 10 10
            RECTANGLE N 64 -384 320 -64 
            LINE N 384 -128 320 -128 
            LINE N 0 -32 64 -32 
            LINE N 0 -128 64 -128 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 0 -192 64 -192 
            LINE N 384 -192 320 -192 
            LINE N 384 -256 320 -256 
            LINE N 384 -320 320 -320 
        END BLOCKDEF
        BEGIN BLOCKDEF vcc
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 64 -32 64 -64 
            LINE N 64 0 64 -32 
            LINE N 96 -64 32 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF d2_4e
            TIMESTAMP 2000 1 1 10 10 10
            RECTANGLE N 64 -384 320 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -256 64 -256 
            LINE N 0 -320 64 -320 
            LINE N 384 -128 320 -128 
            LINE N 384 -192 320 -192 
            LINE N 384 -256 320 -256 
            LINE N 384 -320 320 -320 
        END BLOCKDEF
        BEGIN BLOCKDEF title
            TIMESTAMP 2000 1 1 10 10 10
            LINE N -764 -288 -796 -256 
            LINE N -732 -256 -764 -288 
            LINE N -776 -256 -732 -256 
            LINE N -788 -264 -776 -256 
            LINE N -840 -256 -796 -256 
            LINE N -804 -256 -836 -288 
            LINE N -800 -256 -832 -288 
            LINE N -796 -256 -828 -288 
            LINE N -832 -288 -800 -320 
            LINE N -828 -288 -796 -320 
            LINE N -828 -352 -796 -384 
            LINE N -840 -384 -796 -384 
            LINE N -796 -384 -764 -352 
            LINE N -800 -320 -832 -352 
            LINE N -796 -320 -828 -352 
            LINE N -804 -320 -836 -352 
            LINE N -832 -352 -800 -384 
            LINE N -836 -352 -804 -384 
            LINE N -872 -352 -840 -384 
            LINE N -868 -352 -836 -384 
            LINE N -732 -384 -764 -352 
            LINE N -776 -384 -732 -384 
            LINE N -788 -376 -776 -384 
            LINE N -764 -356 -736 -384 
            LINE N -768 -360 -740 -384 
            LINE N -768 -356 -740 -384 
            LINE N -772 -360 -744 -384 
            LINE N -772 -360 -748 -384 
            LINE N -772 -360 -752 -384 
            LINE N -840 -352 -808 -384 
            LINE N -844 -352 -812 -384 
            LINE N -848 -352 -816 -384 
            LINE N -852 -352 -820 -384 
            LINE N -816 -256 -848 -288 
            LINE N -820 -256 -852 -288 
            LINE N -872 -352 -828 -352 
            LINE N -836 -320 -868 -352 
            LINE N -832 -320 -864 -352 
            LINE N -828 -320 -860 -352 
            LINE N -824 -320 -856 -352 
            LINE N -872 -288 -840 -320 
            LINE N -872 -288 -828 -288 
            LINE N -860 -352 -828 -384 
            LINE N -864 -352 -832 -384 
            LINE N -856 -352 -824 -384 
            LINE N -856 -288 -824 -320 
            LINE N -852 -288 -820 -320 
            LINE N -848 -288 -816 -320 
            LINE N -844 -288 -812 -320 
            LINE N -840 -288 -808 -320 
            LINE N -836 -288 -804 -320 
            LINE N -868 -288 -836 -320 
            LINE N -864 -288 -832 -320 
            LINE N -860 -288 -828 -320 
            LINE N -840 -320 -872 -352 
            LINE N -820 -320 -852 -352 
            LINE N -816 -320 -848 -352 
            LINE N -812 -320 -844 -352 
            LINE N -808 -320 -840 -352 
            LINE N -808 -256 -840 -288 
            LINE N -812 -256 -844 -288 
            LINE N -836 -256 -868 -288 
            LINE N -840 -256 -872 -288 
            LINE N -824 -256 -856 -288 
            LINE N -828 -256 -860 -288 
            LINE N -832 -256 -864 -288 
            LINE N -772 -364 -756 -384 
            LINE N -776 -364 -756 -384 
            LINE N -776 -368 -760 -384 
            LINE N -780 -368 -764 -384 
            LINE N -780 -372 -768 -384 
            LINE N -784 -372 -772 -384 
            LINE N -784 -376 -772 -384 
            LINE N -612 -272 -612 -368 
            LINE N -616 -272 -616 -368 
            LINE N -620 -272 -620 -368 
            LINE N -564 -276 -612 -276 
            LINE N -456 -272 -456 -368 
            LINE N -460 -272 -460 -368 
            LINE N -640 -272 -640 -368 
            LINE N -392 -272 -444 -368 
            LINE N -392 -368 -444 -272 
            LINE N -660 -272 -712 -368 
            LINE N -660 -368 -716 -272 
            LINE N -544 -272 -544 -368 
            LINE N -644 -272 -644 -368 
            LINE N -636 -272 -636 -368 
            LINE N -656 -272 -708 -368 
            LINE N -468 -272 -520 -368 
            LINE N -660 -272 -716 -368 
            LINE N -664 -272 -720 -368 
            LINE N -524 -272 -524 -368 
            LINE N -528 -272 -528 -368 
            LINE N -632 -272 -632 -368 
            LINE N -468 -272 -524 -368 
            LINE N -540 -272 -540 -368 
            LINE N -464 -272 -516 -368 
            LINE N -460 -272 -516 -368 
            LINE N -548 -272 -548 -368 
            LINE N -388 -272 -440 -368 
            LINE N -564 -272 -612 -272 
            LINE N -664 -368 -720 -272 
            LINE N -772 -256 -784 -264 
            LINE N -784 -268 -772 -256 
            LINE N -768 -256 -780 -268 
            LINE N -780 -272 -764 -256 
            LINE N -760 -256 -776 -272 
            LINE N -776 -276 -756 -256 
            LINE N -756 -256 -772 -276 
            LINE N -772 -280 -752 -256 
            LINE N -748 -256 -772 -280 
            LINE N -772 -280 -744 -256 
            LINE N -740 -256 -768 -280 
            LINE N -768 -284 -740 -256 
            LINE N -736 -256 -764 -284 
            LINE N -388 -272 -436 -368 
            LINE N -384 -272 -436 -368 
            LINE N -388 -368 -440 -272 
            LINE N -112 -176 -1140 -176 
            BEGIN LINE W -1136 -416 -1136 -212 
            END LINE
            BEGIN LINE W -80 -416 -80 -220 
            END LINE
            BEGIN LINE W -1136 -416 -80 -416 
            END LINE
            LINE N -1136 -128 -80 -128 
            LINE N -1132 -220 -80 -220 
            BEGIN LINE W -80 -80 -352 -80 
            END LINE
            BEGIN LINE W -1136 -80 -352 -80 
            END LINE
            BEGIN LINE W -1136 -224 -1136 -80 
            END LINE
            BEGIN LINE W -144 -80 -152 -80 
            END LINE
            BEGIN LINE W -80 -224 -80 -80 
            END LINE
            LINE N -112 -176 -80 -176 
            LINE N -176 -128 -144 -128 
            LINE N -296 -128 -296 -80 
        END BLOCKDEF
        BEGIN BLOCKDEF nand2
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 216 -96 
            CIRCLE N 192 -108 216 -84 
            LINE N 64 -48 64 -144 
            LINE N 64 -144 144 -144 
            LINE N 144 -48 64 -48 
            ARC N 96 -144 192 -48 144 -48 144 -144 
        END BLOCKDEF
        BEGIN BLOCKDEF DEC7SEG
            TIMESTAMP 2009 3 27 10 5 19
            RECTANGLE N 64 -64 320 0 
            RECTANGLE N 0 -44 64 -20 
            LINE N 64 -32 0 -32 
            RECTANGLE N 320 -44 384 -20 
            LINE N 320 -32 384 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF m4_1e
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -416 96 -416 
            LINE N 0 -352 96 -352 
            LINE N 0 -288 96 -288 
            LINE N 0 -224 96 -224 
            LINE N 0 -32 96 -32 
            LINE N 320 -320 256 -320 
            LINE N 0 -160 96 -160 
            LINE N 0 -96 96 -96 
            LINE N 176 -96 96 -96 
            LINE N 176 -208 176 -96 
            LINE N 224 -32 96 -32 
            LINE N 224 -216 224 -32 
            LINE N 256 -224 96 -192 
            LINE N 256 -416 256 -224 
            LINE N 96 -448 256 -416 
            LINE N 96 -192 96 -448 
            LINE N 128 -160 96 -160 
            LINE N 128 -200 128 -160 
        END BLOCKDEF
        BEGIN BLOCKDEF inv
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -32 64 -32 
            LINE N 224 -32 160 -32 
            LINE N 64 -64 128 -32 
            LINE N 128 -32 64 0 
            LINE N 64 0 64 -64 
            CIRCLE N 128 -48 160 -16 
        END BLOCKDEF
        BEGIN BLOCKDEF Mux4_1_Bus4
            TIMESTAMP 2009 4 23 9 44 40
            LINE N 288 -208 224 -208 
            LINE N 144 -96 144 0 
            LINE N 224 -112 64 -80 
            LINE N 224 -304 224 -112 
            LINE N 64 -336 224 -304 
            LINE N 64 -80 64 -336 
            LINE N 96 -48 64 -48 
            LINE N 96 -88 96 -48 
            LINE N 144 0 0 0 
            LINE N 64 -304 0 -304 
            LINE N 64 -240 0 -240 
            LINE N 64 -176 0 -176 
            LINE N 64 -112 0 -112 
            LINE N 64 -48 0 -48 
            RECTANGLE N 0 -316 64 -292 
            RECTANGLE N 0 -252 64 -228 
            RECTANGLE N 0 -188 64 -164 
            RECTANGLE N 0 -124 64 -100 
            RECTANGLE N 224 -220 288 -196 
        END BLOCKDEF
        BEGIN BLOCK XLXI_50 title
            ATTR TitleFieldText "         Gestion des 4 afficheurs 8 segments"
            ATTR NameFieldText "          (c) 2009 - ISIMA - E. Mesnard"
        END BLOCK
        BEGIN BLOCK XLXI_67 nand2
            PIN I0 E_VA
            PIN I1 XLXN_140
            PIN O AFF_A
        END BLOCK
        BEGIN BLOCK XLXI_68 nand2
            PIN I0 E_VB
            PIN I1 XLXN_178
            PIN O AFF_B
        END BLOCK
        BEGIN BLOCK XLXI_70 nand2
            PIN I0 E_VD
            PIN I1 XLXN_180
            PIN O AFF_D
        END BLOCK
        BEGIN BLOCK XLXI_44 d2_4e
            PIN A0 Q(0)
            PIN A1 Q(1)
            PIN E XLXN_160
            PIN D0 XLXN_140
            PIN D1 XLXN_178
            PIN D2 XLXN_179
            PIN D3 XLXN_180
        END BLOCK
        BEGIN BLOCK XLXI_66 vcc
            PIN P XLXN_160
        END BLOCK
        BEGIN BLOCK XLXI_69 nand2
            PIN I0 E_VC
            PIN I1 XLXN_179
            PIN O AFF_C
        END BLOCK
        BEGIN BLOCK XLXI_94 m4_1e
            PIN D0 Pt_A
            PIN D1 Pt_B
            PIN D2 Pt_C
            PIN D3 Pt_D
            PIN E XLXN_237
            PIN S0 Q(0)
            PIN S1 Q(1)
            PIN O XLXN_250
        END BLOCK
        BEGIN BLOCK XLXI_92 vcc
            PIN P XLXN_237
        END BLOCK
        BEGIN BLOCK XLXI_71 DEC7SEG
            PIN V(3:0) V(3:0)
            PIN AFF(6:0) AFF(6:0)
        END BLOCK
        BEGIN BLOCK XLXI_1 cb2ce
            PIN C CLK
            PIN CE XLXN_131
            PIN CLR
            PIN CEO
            PIN Q0 Q(0)
            PIN Q1 Q(1)
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_2 vcc
            PIN P XLXN_131
        END BLOCK
        BEGIN BLOCK XLXI_96 inv
            PIN I XLXN_250
            PIN O AFF(7)
        END BLOCK
        BEGIN BLOCK XLXI_97 Mux4_1_Bus4
            PIN O(3:0) V(3:0)
            PIN A1 Q(1)
            PIN D0(3:0) VA(3:0)
            PIN D1(3:0) VB(3:0)
            PIN D2(3:0) VC(3:0)
            PIN D3(3:0) VD(3:0)
            PIN A0 Q(0)
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 2688 1900
        ATTR LengthUnitName "CM"
        ATTR GridsPerUnit "4"
        BEGIN INSTANCE XLXI_50 2656 1904 R0
        END INSTANCE
        BEGIN BRANCH XLXN_140
            WIRE 1616 288 1680 288
            WIRE 1680 80 1680 288
            WIRE 1680 80 1984 80
        END BRANCH
        INSTANCE XLXI_67 1984 208 R0
        INSTANCE XLXI_68 1984 352 R0
        INSTANCE XLXI_70 1984 640 R0
        BEGIN BRANCH AFF_D
            WIRE 2240 544 2352 544
        END BRANCH
        BEGIN BRANCH AFF_C
            WIRE 2240 400 2352 400
        END BRANCH
        BEGIN BRANCH AFF_B
            WIRE 2240 256 2352 256
        END BRANCH
        BEGIN BRANCH AFF_A
            WIRE 2240 112 2352 112
        END BRANCH
        BEGIN BRANCH Q(0)
            WIRE 1072 288 1152 288
            WIRE 1152 288 1232 288
            BEGIN DISPLAY 1152 288 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 1072 352 1152 352
            WIRE 1152 352 1232 352
            BEGIN DISPLAY 1152 352 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_44 1232 608 R0
        BEGIN BRANCH XLXN_160
            WIRE 1200 480 1232 480
        END BRANCH
        INSTANCE XLXI_66 1200 544 R270
        BEGIN BRANCH XLXN_178
            WIRE 1616 352 1744 352
            WIRE 1744 224 1984 224
            WIRE 1744 224 1744 352
        END BRANCH
        INSTANCE XLXI_69 1984 496 R0
        BEGIN BRANCH XLXN_179
            WIRE 1616 416 1744 416
            WIRE 1744 368 1984 368
            WIRE 1744 368 1744 416
        END BRANCH
        BEGIN BRANCH XLXN_180
            WIRE 1616 480 1744 480
            WIRE 1744 480 1744 512
            WIRE 1744 512 1984 512
        END BRANCH
        BEGIN BRANCH E_VA
            WIRE 1952 144 1984 144
        END BRANCH
        BEGIN BRANCH E_VB
            WIRE 1952 288 1984 288
        END BRANCH
        BEGIN BRANCH E_VC
            WIRE 1952 432 1984 432
        END BRANCH
        BEGIN BRANCH E_VD
            WIRE 1952 576 1984 576
        END BRANCH
        IOMARKER 2352 544 AFF_D R0 28
        IOMARKER 2352 400 AFF_C R0 28
        IOMARKER 2352 256 AFF_B R0 28
        IOMARKER 2352 112 AFF_A R0 28
        IOMARKER 1952 144 E_VA R180 28
        IOMARKER 1952 288 E_VB R180 28
        IOMARKER 1952 432 E_VC R180 28
        IOMARKER 1952 576 E_VD R180 28
        INSTANCE XLXI_94 1744 1200 R0
        BEGIN BRANCH XLXN_237
            WIRE 1712 1168 1744 1168
        END BRANCH
        INSTANCE XLXI_92 1712 1232 R270
        BEGIN BRANCH Q(0)
            WIRE 1584 1040 1664 1040
            WIRE 1664 1040 1744 1040
            BEGIN DISPLAY 1664 1040 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 1584 1104 1664 1104
            WIRE 1664 1104 1744 1104
            BEGIN DISPLAY 1664 1104 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH V(3:0)
            WIRE 768 1056 816 1056
            WIRE 816 1056 864 1056
            BEGIN DISPLAY 816 1056 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN INSTANCE XLXI_71 864 1088 R0
        END INSTANCE
        BEGIN BRANCH AFF(6:0)
            WIRE 1248 1056 1344 1056
            WIRE 1344 1056 1344 1360
            WIRE 1344 1360 1744 1360
            WIRE 1744 1360 2272 1360
            BEGIN DISPLAY 1744 1360 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH AFF(7:0)
            WIRE 2320 1040 2384 1040
            WIRE 2384 1040 2528 1040
            WIRE 2320 1040 2320 1424
            BEGIN DISPLAY 2384 1040 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        IOMARKER 2528 1040 AFF(7:0) R0 28
        RECTANGLE N 2260 1220 2316 1392 
        INSTANCE XLXI_1 304 592 R0
        BEGIN BRANCH CLK
            WIRE 240 464 304 464
        END BRANCH
        BEGIN BRANCH XLXN_131
            WIRE 240 400 304 400
        END BRANCH
        INSTANCE XLXI_2 240 464 R270
        BEGIN BRANCH Q(0)
            WIRE 688 272 768 272
            WIRE 768 272 848 272
            BEGIN DISPLAY 768 272 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 688 336 768 336
            WIRE 768 336 848 336
            BEGIN DISPLAY 768 336 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        IOMARKER 240 464 CLK R180 28
        BEGIN BRANCH Pt_D
            WIRE 1680 976 1712 976
            WIRE 1712 976 1744 976
        END BRANCH
        BEGIN BRANCH Pt_C
            WIRE 1680 912 1712 912
            WIRE 1712 912 1744 912
        END BRANCH
        BEGIN BRANCH Pt_B
            WIRE 1680 848 1712 848
            WIRE 1712 848 1744 848
        END BRANCH
        BEGIN BRANCH Pt_A
            WIRE 1680 784 1712 784
            WIRE 1712 784 1744 784
        END BRANCH
        IOMARKER 1680 784 Pt_A R180 28
        IOMARKER 1680 848 Pt_B R180 28
        IOMARKER 1680 912 Pt_C R180 28
        IOMARKER 1680 976 Pt_D R180 28
        BEGIN BRANCH AFF(7)
            WIRE 2096 1136 2096 1248
            WIRE 2096 1248 2144 1248
            WIRE 2144 1248 2272 1248
            BEGIN DISPLAY 2144 1248 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_96 2064 912 R90
        BEGIN BRANCH XLXN_250
            WIRE 2064 880 2096 880
            WIRE 2096 880 2096 912
        END BRANCH
        BEGIN BRANCH VA(3:0)
            WIRE 400 960 480 960
        END BRANCH
        BEGIN BRANCH VB(3:0)
            WIRE 400 1024 480 1024
        END BRANCH
        BEGIN BRANCH VC(3:0)
            WIRE 400 1088 480 1088
        END BRANCH
        BEGIN BRANCH VD(3:0)
            WIRE 400 1152 480 1152
        END BRANCH
        BEGIN INSTANCE XLXI_97 480 1264 R0
        END INSTANCE
        IOMARKER 400 960 VA(3:0) R180 28
        IOMARKER 400 1024 VB(3:0) R180 28
        IOMARKER 400 1088 VC(3:0) R180 28
        IOMARKER 400 1152 VD(3:0) R180 28
        BEGIN BRANCH Q(1)
            WIRE 368 1216 480 1216
            BEGIN DISPLAY 368 1216 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(0)
            WIRE 368 1264 480 1264
            BEGIN DISPLAY 368 1264 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(1:0)
            WIRE 960 224 960 496
            BEGIN DISPLAY 960 224 ATTR Name
                ALIGNMENT HARD-BCENTER
            END DISPLAY
        END BRANCH
    END SHEET
END SCHEMATIC

--------------------------------------------------------------------------------
-- Copyright (c) 1995-2008 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 10.1
--  \   \         Application : sch2vhdl
--  /   /         Filename : AFF8SEG.vhf
-- /___/   /\     Timestamp : 03/05/2010 17:17:52
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx\10.1\ISE\bin\nt\unwrapped\sch2vhdl.exe -intstyle ise -family spartan3e -flat -suppress -w "C:/TP Circuits/G12/compteur16bit/AFF8SEG.sch" AFF8SEG.vhf
--Design Name: AFF8SEG
--Device: spartan3e
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesis and simulted, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity FTCE_MXILINX_AFF8SEG is
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          T   : in    std_logic; 
          Q   : out   std_logic);
end FTCE_MXILINX_AFF8SEG;

architecture BEHAVIORAL of FTCE_MXILINX_AFF8SEG is
   attribute BOX_TYPE   : string ;
   attribute INIT       : string ;
   attribute RLOC       : string ;
   signal TQ      : std_logic;
   signal Q_DUMMY : std_logic;
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component FDCE
      -- synopsys translate_off
      generic( INIT : bit :=  '0');
      -- synopsys translate_on
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute INIT of FDCE : component is "0";
   attribute BOX_TYPE of FDCE : component is "BLACK_BOX";
   
   attribute RLOC of I_36_35 : label is "X0Y0";
begin
   Q <= Q_DUMMY;
   I_36_32 : XOR2
      port map (I0=>T,
                I1=>Q_DUMMY,
                O=>TQ);
   
   I_36_35 : FDCE
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                D=>TQ,
                Q=>Q_DUMMY);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity CB2CE_MXILINX_AFF8SEG is
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          CEO : out   std_logic; 
          Q0  : out   std_logic; 
          Q1  : out   std_logic; 
          TC  : out   std_logic);
end CB2CE_MXILINX_AFF8SEG;

architecture BEHAVIORAL of CB2CE_MXILINX_AFF8SEG is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal XLXN_1   : std_logic;
   signal Q0_DUMMY : std_logic;
   signal Q1_DUMMY : std_logic;
   signal TC_DUMMY : std_logic;
   component FTCE_MXILINX_AFF8SEG
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             T   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   attribute HU_SET of I_Q0 : label is "I_Q0_0";
   attribute HU_SET of I_Q1 : label is "I_Q1_1";
begin
   Q0 <= Q0_DUMMY;
   Q1 <= Q1_DUMMY;
   TC <= TC_DUMMY;
   I_Q0 : FTCE_MXILINX_AFF8SEG
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                T=>XLXN_1,
                Q=>Q0_DUMMY);
   
   I_Q1 : FTCE_MXILINX_AFF8SEG
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                T=>Q0_DUMMY,
                Q=>Q1_DUMMY);
   
   I_36_37 : AND2
      port map (I0=>Q1_DUMMY,
                I1=>Q0_DUMMY,
                O=>TC_DUMMY);
   
   I_36_47 : VCC
      port map (P=>XLXN_1);
   
   I_36_52 : AND2
      port map (I0=>CE,
                I1=>TC_DUMMY,
                O=>CEO);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity M2_1E_MXILINX_AFF8SEG is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          E  : in    std_logic; 
          S0 : in    std_logic; 
          O  : out   std_logic);
end M2_1E_MXILINX_AFF8SEG;

architecture BEHAVIORAL of M2_1E_MXILINX_AFF8SEG is
   attribute BOX_TYPE   : string ;
   signal M0 : std_logic;
   signal M1 : std_logic;
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component AND3B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B1 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
begin
   I_36_30 : AND3
      port map (I0=>D1,
                I1=>E,
                I2=>S0,
                O=>M1);
   
   I_36_31 : AND3B1
      port map (I0=>S0,
                I1=>E,
                I2=>D0,
                O=>M0);
   
   I_36_38 : OR2
      port map (I0=>M1,
                I1=>M0,
                O=>O);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity M4_1E_MXILINX_AFF8SEG is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          D2 : in    std_logic; 
          D3 : in    std_logic; 
          E  : in    std_logic; 
          S0 : in    std_logic; 
          S1 : in    std_logic; 
          O  : out   std_logic);
end M4_1E_MXILINX_AFF8SEG;

architecture BEHAVIORAL of M4_1E_MXILINX_AFF8SEG is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal M01 : std_logic;
   signal M23 : std_logic;
   component M2_1E_MXILINX_AFF8SEG
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             E  : in    std_logic; 
             S0 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component MUXF5
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             S  : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of MUXF5 : component is "BLACK_BOX";
   
   attribute HU_SET of I_M01 : label is "I_M01_3";
   attribute HU_SET of I_M23 : label is "I_M23_2";
begin
   I_M01 : M2_1E_MXILINX_AFF8SEG
      port map (D0=>D0,
                D1=>D1,
                E=>E,
                S0=>S0,
                O=>M01);
   
   I_M23 : M2_1E_MXILINX_AFF8SEG
      port map (D0=>D2,
                D1=>D3,
                E=>E,
                S0=>S0,
                O=>M23);
   
   I_O : MUXF5
      port map (I0=>M01,
                I1=>M23,
                S=>S1,
                O=>O);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity D2_4E_MXILINX_AFF8SEG is
   port ( A0 : in    std_logic; 
          A1 : in    std_logic; 
          E  : in    std_logic; 
          D0 : out   std_logic; 
          D1 : out   std_logic; 
          D2 : out   std_logic; 
          D3 : out   std_logic);
end D2_4E_MXILINX_AFF8SEG;

architecture BEHAVIORAL of D2_4E_MXILINX_AFF8SEG is
   attribute BOX_TYPE   : string ;
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component AND3B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B1 : component is "BLACK_BOX";
   
   component AND3B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B2 : component is "BLACK_BOX";
   
begin
   I_36_30 : AND3
      port map (I0=>A1,
                I1=>A0,
                I2=>E,
                O=>D3);
   
   I_36_31 : AND3B1
      port map (I0=>A0,
                I1=>A1,
                I2=>E,
                O=>D2);
   
   I_36_32 : AND3B1
      port map (I0=>A1,
                I1=>A0,
                I2=>E,
                O=>D1);
   
   I_36_33 : AND3B2
      port map (I0=>A0,
                I1=>A1,
                I2=>E,
                O=>D0);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity AFF8SEG is
   port ( CLK   : in    std_logic; 
          E_VA  : in    std_logic; 
          E_VB  : in    std_logic; 
          E_VC  : in    std_logic; 
          E_VD  : in    std_logic; 
          Pt_A  : in    std_logic; 
          Pt_B  : in    std_logic; 
          Pt_C  : in    std_logic; 
          Pt_D  : in    std_logic; 
          VA    : in    std_logic_vector (3 downto 0); 
          VB    : in    std_logic_vector (3 downto 0); 
          VC    : in    std_logic_vector (3 downto 0); 
          VD    : in    std_logic_vector (3 downto 0); 
          AFF   : out   std_logic_vector (7 downto 0); 
          AFF_A : out   std_logic; 
          AFF_B : out   std_logic; 
          AFF_C : out   std_logic; 
          AFF_D : out   std_logic);
end AFF8SEG;

architecture BEHAVIORAL of AFF8SEG is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal Q                     : std_logic_vector (1 downto 0);
   signal V                     : std_logic_vector (3 downto 0);
   signal XLXN_131              : std_logic;
   signal XLXN_140              : std_logic;
   signal XLXN_160              : std_logic;
   signal XLXN_178              : std_logic;
   signal XLXN_179              : std_logic;
   signal XLXN_180              : std_logic;
   signal XLXN_237              : std_logic;
   signal XLXN_250              : std_logic;
   signal XLXI_1_CLR_openSignal : std_logic;
   component CB2CE_MXILINX_AFF8SEG
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             CEO : out   std_logic; 
             Q0  : out   std_logic; 
             Q1  : out   std_logic; 
             TC  : out   std_logic);
   end component;
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   component D2_4E_MXILINX_AFF8SEG
      port ( A0 : in    std_logic; 
             A1 : in    std_logic; 
             E  : in    std_logic; 
             D0 : out   std_logic; 
             D1 : out   std_logic; 
             D2 : out   std_logic; 
             D3 : out   std_logic);
   end component;
   
   component NAND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NAND2 : component is "BLACK_BOX";
   
   component DEC7SEG
      port ( V   : in    std_logic_vector (3 downto 0); 
             AFF : out   std_logic_vector (6 downto 0));
   end component;
   
   component M4_1E_MXILINX_AFF8SEG
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             D2 : in    std_logic; 
             D3 : in    std_logic; 
             E  : in    std_logic; 
             S0 : in    std_logic; 
             S1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
   component Mux4_1_Bus4
      port ( O  : out   std_logic_vector (3 downto 0); 
             A1 : in    std_logic; 
             D0 : in    std_logic_vector (3 downto 0); 
             D1 : in    std_logic_vector (3 downto 0); 
             D2 : in    std_logic_vector (3 downto 0); 
             D3 : in    std_logic_vector (3 downto 0); 
             A0 : in    std_logic);
   end component;
   
   attribute HU_SET of XLXI_1 : label is "XLXI_1_6";
   attribute HU_SET of XLXI_44 : label is "XLXI_44_4";
   attribute HU_SET of XLXI_94 : label is "XLXI_94_5";
begin
   XLXI_1 : CB2CE_MXILINX_AFF8SEG
      port map (C=>CLK,
                CE=>XLXN_131,
                CLR=>XLXI_1_CLR_openSignal,
                CEO=>open,
                Q0=>Q(0),
                Q1=>Q(1),
                TC=>open);
   
   XLXI_2 : VCC
      port map (P=>XLXN_131);
   
   XLXI_44 : D2_4E_MXILINX_AFF8SEG
      port map (A0=>Q(0),
                A1=>Q(1),
                E=>XLXN_160,
                D0=>XLXN_140,
                D1=>XLXN_178,
                D2=>XLXN_179,
                D3=>XLXN_180);
   
   XLXI_66 : VCC
      port map (P=>XLXN_160);
   
   XLXI_67 : NAND2
      port map (I0=>E_VA,
                I1=>XLXN_140,
                O=>AFF_A);
   
   XLXI_68 : NAND2
      port map (I0=>E_VB,
                I1=>XLXN_178,
                O=>AFF_B);
   
   XLXI_69 : NAND2
      port map (I0=>E_VC,
                I1=>XLXN_179,
                O=>AFF_C);
   
   XLXI_70 : NAND2
      port map (I0=>E_VD,
                I1=>XLXN_180,
                O=>AFF_D);
   
   XLXI_71 : DEC7SEG
      port map (V(3 downto 0)=>V(3 downto 0),
                AFF(6 downto 0)=>AFF(6 downto 0));
   
   XLXI_92 : VCC
      port map (P=>XLXN_237);
   
   XLXI_94 : M4_1E_MXILINX_AFF8SEG
      port map (D0=>Pt_A,
                D1=>Pt_B,
                D2=>Pt_C,
                D3=>Pt_D,
                E=>XLXN_237,
                S0=>Q(0),
                S1=>Q(1),
                O=>XLXN_250);
   
   XLXI_96 : INV
      port map (I=>XLXN_250,
                O=>AFF(7));
   
   XLXI_97 : Mux4_1_Bus4
      port map (A0=>Q(0),
                A1=>Q(1),
                D0(3 downto 0)=>VA(3 downto 0),
                D1(3 downto 0)=>VB(3 downto 0),
                D2(3 downto 0)=>VC(3 downto 0),
                D3(3 downto 0)=>VD(3 downto 0),
                O(3 downto 0)=>V(3 downto 0));
   
end BEHAVIORAL;



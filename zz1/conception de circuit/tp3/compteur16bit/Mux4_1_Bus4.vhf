--------------------------------------------------------------------------------
-- Copyright (c) 1995-2008 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 10.1
--  \   \         Application : sch2vhdl
--  /   /         Filename : Mux4_1_Bus4.vhf
-- /___/   /\     Timestamp : 03/05/2010 17:17:52
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx\10.1\ISE\bin\nt\unwrapped\sch2vhdl.exe -intstyle ise -family spartan3e -flat -suppress -w "C:/TP Circuits/G12/compteur16bit/Mux4_1_Bus4.sch" Mux4_1_Bus4.vhf
--Design Name: Mux4_1_Bus4
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

entity Mux4_1_Bus4 is
   port ( A0 : in    std_logic; 
          A1 : in    std_logic; 
          D0 : in    std_logic_vector (3 downto 0); 
          D1 : in    std_logic_vector (3 downto 0); 
          D2 : in    std_logic_vector (3 downto 0); 
          D3 : in    std_logic_vector (3 downto 0); 
          O  : out   std_logic_vector (3 downto 0));
end Mux4_1_Bus4;

architecture BEHAVIORAL of Mux4_1_Bus4 is
   attribute BOX_TYPE   : string ;
   signal XLXN_1   : std_logic;
   signal XLXN_2   : std_logic;
   signal XLXN_16  : std_logic;
   signal XLXN_18  : std_logic;
   signal XLXN_19  : std_logic;
   signal XLXN_20  : std_logic;
   signal XLXN_34  : std_logic;
   signal XLXN_36  : std_logic;
   signal XLXN_37  : std_logic;
   signal XLXN_38  : std_logic;
   signal XLXN_52  : std_logic;
   signal XLXN_54  : std_logic;
   signal XLXN_84  : std_logic;
   signal XLXN_85  : std_logic;
   signal XLXN_99  : std_logic;
   signal XLXN_101 : std_logic;
   component AND3B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B1 : component is "BLACK_BOX";
   
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component AND3B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B2 : component is "BLACK_BOX";
   
   component OR4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR4 : component is "BLACK_BOX";
   
begin
   XLXI_109 : AND3B1
      port map (I0=>A1,
                I1=>A0,
                I2=>D1(0),
                O=>XLXN_16);
   
   XLXI_110 : AND3B1
      port map (I0=>A0,
                I1=>A1,
                I2=>D2(0),
                O=>XLXN_18);
   
   XLXI_111 : AND3
      port map (I0=>A1,
                I1=>A0,
                I2=>D3(0),
                O=>XLXN_2);
   
   XLXI_112 : AND3B2
      port map (I0=>A1,
                I1=>A0,
                I2=>D0(0),
                O=>XLXN_1);
   
   XLXI_113 : OR4
      port map (I0=>XLXN_2,
                I1=>XLXN_18,
                I2=>XLXN_16,
                I3=>XLXN_1,
                O=>O(0));
   
   XLXI_114 : AND3B2
      port map (I0=>A1,
                I1=>A0,
                I2=>D0(2),
                O=>XLXN_37);
   
   XLXI_115 : AND3B1
      port map (I0=>A1,
                I1=>A0,
                I2=>D1(2),
                O=>XLXN_52);
   
   XLXI_116 : AND3B1
      port map (I0=>A0,
                I1=>A1,
                I2=>D2(2),
                O=>XLXN_54);
   
   XLXI_117 : AND3
      port map (I0=>A1,
                I1=>A0,
                I2=>D3(2),
                O=>XLXN_38);
   
   XLXI_131 : AND3B1
      port map (I0=>A1,
                I1=>A0,
                I2=>D1(1),
                O=>XLXN_34);
   
   XLXI_132 : AND3B1
      port map (I0=>A0,
                I1=>A1,
                I2=>D2(1),
                O=>XLXN_36);
   
   XLXI_133 : AND3
      port map (I0=>A1,
                I1=>A0,
                I2=>D3(1),
                O=>XLXN_20);
   
   XLXI_134 : AND3B2
      port map (I0=>A1,
                I1=>A0,
                I2=>D0(1),
                O=>XLXN_19);
   
   XLXI_135 : OR4
      port map (I0=>XLXN_20,
                I1=>XLXN_36,
                I2=>XLXN_34,
                I3=>XLXN_19,
                O=>O(1));
   
   XLXI_140 : OR4
      port map (I0=>XLXN_38,
                I1=>XLXN_54,
                I2=>XLXN_52,
                I3=>XLXN_37,
                O=>O(2));
   
   XLXI_141 : AND3B1
      port map (I0=>A1,
                I1=>A0,
                I2=>D1(3),
                O=>XLXN_99);
   
   XLXI_142 : AND3B1
      port map (I0=>A0,
                I1=>A1,
                I2=>D2(3),
                O=>XLXN_101);
   
   XLXI_143 : AND3
      port map (I0=>A1,
                I1=>A0,
                I2=>D3(3),
                O=>XLXN_85);
   
   XLXI_144 : AND3B2
      port map (I0=>A1,
                I1=>A0,
                I2=>D0(3),
                O=>XLXN_84);
   
   XLXI_145 : OR4
      port map (I0=>XLXN_85,
                I1=>XLXN_101,
                I2=>XLXN_99,
                I3=>XLXN_84,
                O=>O(3));
   
end BEHAVIORAL;



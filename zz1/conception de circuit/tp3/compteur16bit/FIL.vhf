--------------------------------------------------------------------------------
-- Copyright (c) 1995-2008 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 10.1
--  \   \         Application : sch2vhdl
--  /   /         Filename : FIL.vhf
-- /___/   /\     Timestamp : 03/05/2010 17:17:54
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx\10.1\ISE\bin\nt\unwrapped\sch2vhdl.exe -intstyle ise -family spartan3e -flat -suppress -w "C:/TP Circuits/G12/compteur16bit/FIL.sch" FIL.vhf
--Design Name: FIL
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

entity FIL is
   port ( e : in    std_logic; 
          s : out   std_logic);
end FIL;

architecture BEHAVIORAL of FIL is
   attribute BOX_TYPE   : string ;
   signal XLXN_2 : std_logic;
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   XLXI_4 : INV
      port map (I=>e,
                O=>XLXN_2);
   
   XLXI_5 : INV
      port map (I=>XLXN_2,
                O=>s);
   
end BEHAVIORAL;



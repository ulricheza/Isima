--------------------------------------------------------------------------------
-- Copyright (c) 1995-2008 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 10.1
--  \   \         Application : sch2vhdl
--  /   /         Filename : DEC7SEG.vhf
-- /___/   /\     Timestamp : 03/05/2010 17:17:53
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx\10.1\ISE\bin\nt\unwrapped\sch2vhdl.exe -intstyle ise -family spartan3e -flat -suppress -w "C:/TP Circuits/G12/compteur16bit/DEC7SEG.sch" DEC7SEG.vhf
--Design Name: DEC7SEG
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

entity DEC7SEG is
   port ( V   : in    std_logic_vector (3 downto 0); 
          AFF : out   std_logic_vector (6 downto 0));
end DEC7SEG;

architecture BEHAVIORAL of DEC7SEG is
   attribute INIT       : string ;
   attribute BOX_TYPE   : string ;
   component ROM16X1
      -- synopsys translate_off
      generic( INIT : bit_vector :=  x"0000");
      -- synopsys translate_on
      port ( A0 : in    std_logic; 
             A1 : in    std_logic; 
             A2 : in    std_logic; 
             A3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute INIT of ROM16X1 : component is "0000";
   attribute BOX_TYPE of ROM16X1 : component is "BLACK_BOX";
   
   attribute INIT of XLXI_58 : label is "2812";
   attribute INIT of XLXI_59 : label is "D860";
   attribute INIT of XLXI_60 : label is "D004";
   attribute INIT of XLXI_61 : label is "8492";
   attribute INIT of XLXI_62 : label is "02BA";
   attribute INIT of XLXI_63 : label is "208E";
   attribute INIT of XLXI_64 : label is "1083";
begin
   XLXI_58 : ROM16X1
   -- synopsys translate_off
   generic map( INIT => x"2812")
   -- synopsys translate_on
      port map (A0=>V(0),
                A1=>V(1),
                A2=>V(2),
                A3=>V(3),
                O=>AFF(0));
   
   XLXI_59 : ROM16X1
   -- synopsys translate_off
   generic map( INIT => x"D860")
   -- synopsys translate_on
      port map (A0=>V(0),
                A1=>V(1),
                A2=>V(2),
                A3=>V(3),
                O=>AFF(1));
   
   XLXI_60 : ROM16X1
   -- synopsys translate_off
   generic map( INIT => x"D004")
   -- synopsys translate_on
      port map (A0=>V(0),
                A1=>V(1),
                A2=>V(2),
                A3=>V(3),
                O=>AFF(2));
   
   XLXI_61 : ROM16X1
   -- synopsys translate_off
   generic map( INIT => x"8492")
   -- synopsys translate_on
      port map (A0=>V(0),
                A1=>V(1),
                A2=>V(2),
                A3=>V(3),
                O=>AFF(3));
   
   XLXI_62 : ROM16X1
   -- synopsys translate_off
   generic map( INIT => x"02BA")
   -- synopsys translate_on
      port map (A0=>V(0),
                A1=>V(1),
                A2=>V(2),
                A3=>V(3),
                O=>AFF(4));
   
   XLXI_63 : ROM16X1
   -- synopsys translate_off
   generic map( INIT => x"208E")
   -- synopsys translate_on
      port map (A0=>V(0),
                A1=>V(1),
                A2=>V(2),
                A3=>V(3),
                O=>AFF(5));
   
   XLXI_64 : ROM16X1
   -- synopsys translate_off
   generic map( INIT => x"1083")
   -- synopsys translate_on
      port map (A0=>V(0),
                A1=>V(1),
                A2=>V(2),
                A3=>V(3),
                O=>AFF(6));
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;

package long_array is
type array1 is array (63 DOWNTO 0) of integer range 0 to 255;
end long_array;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;
use work.long_array.all;

entity run_length_encoding is
port(
clock : in std_logic;
reset : in std_logic;
image_data_in : in array1;
image_data_out : out array1
);
end run_length_encoding;

architecture behavioral of run_length_encoding is

--signal image_data_out1 : std_logic_vector (63 downto 0);
signal i : integer:=0;
signal m : integer:=0;
signal count : integer:=1;

begin
process(clock)
begin
if rising_edge(clock) then
   for i in 0 to 62 loop
   if (image_data_in(i) = image_data_in(i+1)) then
	  count <= count +1;
	  elsif (image_data_in(i) /= image_data_in(i+1) AND count = 1) then
	  image_data_out(m) <= image_data_in(i);
	  m <=m+1;
	  else 
	  image_data_out(m) <= image_data_in(i);
	  m <=m+1;
	  image_data_out(m) <= count;
	  end if;
end loop;
end if;
end process; 
end behavioral;

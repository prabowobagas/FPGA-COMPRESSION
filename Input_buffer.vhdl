LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.numeric_std.ALL;
ENTITY showspi IS
  Generic(
  addr_depth : integer := 512 --address depth
  ); 
  PORT (
     reset       : in std_logic;
	 raspi_ss0   : in  STD_LOGIC;
	 raspi_ss1   : in  STD_LOGIC;
     raspi_mosi  : in  STD_LOGIC;
	 raspi_miso  : out STD_LOGIC;
	 clk		 : in std_logic;
     raspi_sck   : in  STD_LOGIC;
     
     ram_data_dpo : out std_logic_vector(7 DOWNTO 0)
     
     );
    
END showspi;


ARCHITECTURE bhv OF showspi IS
  signal temp_slave_out_d : std_logic_vector (7 DOWNTO 0):= (others=>'0');
  signal addr_value_a : std_logic_vector (8 DOWNTO 0) := (others=>'0');
  signal addr_assign : std_logic_vector(8 DOWNTO 0); -- number of address 
  signal write_signal_we : std_logic := '0';
  signal ram_read_address_dpra: std_logic_vector(8 DOWNTO 0);
  
COMPONENT VRAM_BUFFER
    PORT (
      a : IN STD_LOGIC_VECTOR(8 DOWNTO 0);
      d : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
      dpra : IN STD_LOGIC_VECTOR(8 DOWNTO 0); -- address assign 2nd port
      clk : IN STD_LOGIC;
      we : IN STD_LOGIC;
      dpo : OUT STD_LOGIC_VECTOR(7 DOWNTO 0) -- data for 2nd port out
    );
  END COMPONENT;
  
BEGIN
	-- buffer 8 bit
	process(raspi_sck,reset) -- saving each 8 bit data
	   variable temp_data : std_logic_vector (7 DOWNTO 0);
	   variable spi_counter: integer:=0;
	   begin
	   if reset = '0' OR raspi_ss0 = '1' then
	       temp_data := (others=>'0');
	       spi_counter := 0;
	   elsif rising_edge(raspi_sck) and raspi_ss0 = '0' then
	       temp_data(7 DOWNTO 1) := temp_data(6 DOWNTO 0);
	       temp_data(0) := raspi_mosi;
	       if(spi_counter = 8) then
	           temp_slave_out_d(7 DOWNTO 0) <= temp_data(7 DOWNTO 0);
	           
	           spi_counter := 0;
	           write_signal_we <= '1'; -- write signal to RAM
	       else
	           spi_counter := spi_counter + 1;
	           write_signal_we <=  '0';
	       end if;
	   end if;  
	   end process;  
	   
    -- address counter, to define the address it needs to put in.
    process(raspi_sck,reset)
    variable addr_increment : integer range 0 to (addr_depth - 1); -- number of address
    begin
    if(reset = '0' or raspi_ss0 = '0') then
        addr_increment := 0;
        addr_value  <= (others=>'0');
        
    elsif (rising_edge(raspi_sck) and raspi_ss0 ='0') then
        addr_increment := addr_increment +  1;
        addr_assign <= std_logic_vector(to_unsigned(addr_increment,8));
        if(addr_increment = addr_depth) then
            addr_increment := 0;
        end if;
    end if;
    end process;
    
    buffer_ram : VRAM_BUFFER
      PORT MAP (
        a => addr_value_a,
        d => temp_slave_out_d,
        dpra => ram_read_address_dpra, -- which address to read
        clk => clk,
        we => write_signal_we,
        dpo => ram_data_dpo --value inside the address
      );
      

            
END bhv;

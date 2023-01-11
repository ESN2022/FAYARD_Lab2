library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


ENTITY FAYARD_Lab2 IS
   PORT(
      clk	  : in  std_logic;
      reset	  : in  std_logic;
		output0 : out std_logic_vector(7 downto 0);
		output1 : out std_logic_vector(7 downto 0);
		output2 : out std_logic_vector(7 downto 0)
      );
END FAYARD_Lab2;


ARCHITECTURE ARCH_FAYARD_Lab2 OF FAYARD_Lab2 IS

component FAYARD_Lab2_sys is
  port (
		clk_clk                          : in  std_logic                    := 'X'; -- clk
		pio_0_external_connection_export : out std_logic_vector(11 downto 0);        -- export
		reset_reset_n                    : in  std_logic                    := 'X'  -- reset_n
  );
end component FAYARD_Lab2_sys;

component bin_to_7seg is
  port (
		input                          	: in  std_logic_vector(3 downto 0);
		output 									: out std_logic_vector(7 downto 0)
  );
end component bin_to_7seg;

signal internal_sig : std_logic_vector(11 downto 0);

begin
	u0 : component FAYARD_Lab2_sys
	port map (
		clk_clk                          => clk,                         
		pio_0_external_connection_export => internal_sig, 
		reset_reset_n                    => reset                     
  );
  
	sev_seg0: component bin_to_7seg
	port map (
		input                          	=> internal_sig(3 downto 0),                         
		output 									=> output0                  
  );
  
   sev_seg1: component bin_to_7seg
	port map (
		input                          	=> internal_sig(7 downto 4),                         
		output 									=> output1                  
  );
  
   sev_seg2: component bin_to_7seg
	port map (
		input                          	=> internal_sig(11 downto 8),                         
		output 									=> output2                  
  );
  
END ARCH_FAYARD_Lab2;


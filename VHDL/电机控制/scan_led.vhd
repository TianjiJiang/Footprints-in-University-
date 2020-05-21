LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY scan_led IS
PORT(
clk_1k:	IN	STD_LOGIC;
d:		IN	STD_LOGIC_VECTOR(31 DOWNTO 0);		--输入要显示的数据
dig:	OUT	STD_LOGIC_VECTOR(7 	DOWNTO 0);		--数码管选择输出引脚
seg:	OUT STD_LOGIC_VECTOR(7 	DOWNTO 0)		--数码管段输出引脚
);
END ENTITY;

ARCHITECTURE one OF scan_led IS
SIGNAL 	seg_r:		STD_LOGIC_VECTOR(7 DOWNTO 0);	--定义数码管输出寄存器
SIGNAL  dig_r:		STD_LOGIC_VECTOR(7 DOWNTO 0);	--定义数码管选择输出寄存器
SIGNAL	disp_dat:	STD_LOGIC_VECTOR(3 DOWNTO 0);		--定义显示数据寄存器
SIGNAL	count:		STD_LOGIC_VECTOR(2 DOWNTO 0);		--定义计数寄存器
BEGIN
dig<=dig_r;
seg<=seg_r;
PROCESS(clk_1k)
BEGIN
	IF	RISING_EDGE(clk_1k) THEN 
		count<=count+1;		
	END IF;
END PROCESS;

PROCESS(clk_1k)
BEGIN
	IF	RISING_EDGE(clk_1k) THEN 
		CASE count IS
		WHEN "000"=>	disp_dat<=d(31 DOWNTO 28);	--第一个数码管
		WHEN "001"=>	disp_dat<=d(27 DOWNTO 24);	--第二个数码管
		WHEN "010"=>	disp_dat<=d(23 DOWNTO 20);	--第三个数码管
		WHEN "011"=>	disp_dat<=d(19 DOWNTO 16);	--第四个数码管
		WHEN "100"=>	disp_dat<=d(15 DOWNTO 12);	--第五个数码管
		WHEN "101"=>	disp_dat<=d(11 DOWNTO 8);	--第六个数码管
		WHEN "110"=>	disp_dat<=d(7 DOWNTO 4);	--第七个数码管
		WHEN "111"=>	disp_dat<=d(3 DOWNTO 0);	--第八个数码管
		END CASE;

		CASE count IS					--选择数码管显示位
		WHEN "000"=>	dig_r<="01111111";		--选择第一个数码管显示
		WHEN "001"=>	dig_r<="10111111";		--选择第二个数码管显示
		WHEN "010"=>	dig_r<="11011111";		--选择第三个数码管显示
		WHEN "011"=>	dig_r<="11101111";		--选择第四个数码管显示
		WHEN "100"=>	dig_r<="11110111";		--选择第五个数码管显示
		WHEN "101"=>	dig_r<="11111011";		--选择第六个数码管显示
		WHEN "110"=>	dig_r<="11111101";		--选择第七个数码管显示
		WHEN "111"=>	dig_r<="11111110";		--选择第八个数码管显示
		END CASE;
	END IF;
END PROCESS;

PROCESS(disp_dat)
BEGIN
	CASE disp_dat IS
		WHEN 	X"0"=>	seg_r<=X"c0";--显示0
		WHEN	X"1"=>	seg_r<=X"f9";--显示1
		WHEN	X"2"=>	seg_r<=X"a4";--显示2
		WHEN	X"3"=>	seg_r<=X"b0";--显示3
		WHEN	X"4"=>	seg_r<=X"99";--显示4
		WHEN	X"5"=>	seg_r<=X"92";--显示5
		WHEN	X"6"=>	seg_r<=X"82";--显示6
		WHEN	X"7"=>	seg_r<=X"f8";--显示7
		WHEN	X"8"=>	seg_r<=X"80";--显示8
		WHEN	X"9"=>	seg_r<=X"90";--显示9
		WHEN	X"a"=>	seg_r<=X"88";--显示a
		WHEN	X"b"=>	seg_r<=X"83";--显示b
		WHEN	X"c"=>	seg_r<=X"c6";--显示c
		WHEN	X"d"=>	seg_r<=X"a1";--显示d
		WHEN	X"e"=>	seg_r<=X"86";--显示e
		WHEN	X"f"=>	seg_r<=X"8e";--显示f
	END CASE;
END PROCESS;
END;
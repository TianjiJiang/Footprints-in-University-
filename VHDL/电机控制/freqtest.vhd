LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY	freqtest IS
PORT(
clock:		IN	STD_LOGIC;						--系统时钟
freq_input:	IN	STD_LOGIC;						--被测信号输入
dig:		OUT	STD_LOGIC_VECTOR(7 DOWNTO 0);	--数码管选择输出引脚
seg:		OUT STD_LOGIC_VECTOR(7 DOWNTO 0);	--数码管段输出引脚
test:		OUT STD_LOGIC_VECTOR(9 DOWNTO 0)	--输出频率信号，用于测试
);
END;

ARCHITECTURE one OF freqtest IS
---------------------------------<<调用10进制计数器模块和数码管显示的模块
COMPONENT cnt10 
PORT(
clk:	IN		STD_LOGIC;					--计数时钟
rst:	IN		STD_LOGIC;					--复位信号
cin:	IN  	STD_LOGIC;					--进位输入
cout:	BUFFER	STD_LOGIC;					--进位输出
dout:	OUT 	STD_LOGIC_VECTOR(3 DOWNTO 0)--计数输出
);
END COMPONENT;

COMPONENT scan_led 
PORT(
clk_1k:	IN	STD_LOGIC;
d:		IN	STD_LOGIC_VECTOR(31 DOWNTO 0);		--输入要显示的数据
dig:	OUT	STD_LOGIC_VECTOR(7 	DOWNTO 0);		--数码管选择输出引脚
seg:	OUT STD_LOGIC_VECTOR(7 	DOWNTO 0)		--数码管段输出引脚
);
END COMPONENT;
------------------------------------->>调用10进制计数器模块和数码管显示的模块
SIGNAL 	counter :	STD_LOGIC_VECTOR(25 DOWNTO 0);		--时钟分频计数器
SIGNAL 	freq_result:	STD_LOGIC_VECTOR(31 DOWNTO 0);	--频率测量结果寄存器
SIGNAL 	pre_freq:	STD_LOGIC_VECTOR(31 DOWNTO 0);			--脉冲计数寄存器
SIGNAL	divide_clk:	STD_LOGIC;			--1Hz闸门信号
SIGNAL	clk_scan:	STD_LOGIC;			--数码管扫描显示时钟
SIGNAL  cout1,cout2,cout3,cout4,cout5,cout6,cout7:STD_LOGIC;
SIGNAL  rst:		STD_LOGIC;------NEW_2006_9_21

BEGIN
clk_scan<=counter(15);	--动态扫描时钟
test<=counter(9 DOWNTO 0);		--输出频率信号，用于测试

PROCESS(clock)		--时钟分频进程：分出1Hz基准信号
BEGIN
	IF	RISING_EDGE(clock) THEN 
		IF divide_clk='1' THEN
			counter<=B"00_0000_0000_0000_0000_0000_0000";
		ELSE
			counter<=counter+1;
		END IF;
	END IF;
END PROCESS;
divide_clk<='1' WHEN (counter>=48000000) ELSE '0';
--<<锁存测量值进程.
PROCESS(clock)
BEGIN
	IF	RISING_EDGE(clock) THEN 
		IF divide_clk='1'  THEN
			freq_result<=pre_freq;	
		END IF;		
	END IF;
END PROCESS;

PROCESS(clock)
BEGIN
	IF	RISING_EDGE(clock) THEN 
		IF divide_clk='1' THEN
			rst<='1';
		ELSE
			rst<='0';
		END IF;		
	END IF;
END PROCESS;

--8位十进制计数模块:由8个十进制计数模块构成
U1:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>'1',  cout=>cout1,dout=>pre_freq(3 DOWNTO 0));
U2:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout1,cout=>cout2,dout=>pre_freq(7  DOWNTO 4));
U3:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout2,cout=>cout3,dout=>pre_freq(11 DOWNTO 8));
U4:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout3,cout=>cout4,dout=>pre_freq(15 DOWNTO 12));
U5:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout4,cout=>cout5,dout=>pre_freq(19 DOWNTO 16));
U6:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout5,cout=>cout6,dout=>pre_freq(23 DOWNTO 20));
U7:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout6,cout=>cout7,dout=>pre_freq(27 DOWNTO 24));
U8:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout7,			dout=>pre_freq(31 DOWNTO 28));

U9:	scan_led PORT	MAP(clk_1k=>clk_scan,d=>freq_result,dig=>dig,seg=>seg);
END;


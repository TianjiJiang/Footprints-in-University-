LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY scan_led IS
PORT(
clk_1k:	IN	STD_LOGIC;
d:		IN	STD_LOGIC_VECTOR(31 DOWNTO 0);		--����Ҫ��ʾ������
dig:	OUT	STD_LOGIC_VECTOR(7 	DOWNTO 0);		--�����ѡ���������
seg:	OUT STD_LOGIC_VECTOR(7 	DOWNTO 0)		--����ܶ��������
);
END ENTITY;

ARCHITECTURE one OF scan_led IS
SIGNAL 	seg_r:		STD_LOGIC_VECTOR(7 DOWNTO 0);	--�������������Ĵ���
SIGNAL  dig_r:		STD_LOGIC_VECTOR(7 DOWNTO 0);	--���������ѡ������Ĵ���
SIGNAL	disp_dat:	STD_LOGIC_VECTOR(3 DOWNTO 0);		--������ʾ���ݼĴ���
SIGNAL	count:		STD_LOGIC_VECTOR(2 DOWNTO 0);		--��������Ĵ���
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
		WHEN "000"=>	disp_dat<=d(31 DOWNTO 28);	--��һ�������
		WHEN "001"=>	disp_dat<=d(27 DOWNTO 24);	--�ڶ��������
		WHEN "010"=>	disp_dat<=d(23 DOWNTO 20);	--�����������
		WHEN "011"=>	disp_dat<=d(19 DOWNTO 16);	--���ĸ������
		WHEN "100"=>	disp_dat<=d(15 DOWNTO 12);	--����������
		WHEN "101"=>	disp_dat<=d(11 DOWNTO 8);	--�����������
		WHEN "110"=>	disp_dat<=d(7 DOWNTO 4);	--���߸������
		WHEN "111"=>	disp_dat<=d(3 DOWNTO 0);	--�ڰ˸������
		END CASE;

		CASE count IS					--ѡ���������ʾλ
		WHEN "000"=>	dig_r<="01111111";		--ѡ���һ���������ʾ
		WHEN "001"=>	dig_r<="10111111";		--ѡ��ڶ����������ʾ
		WHEN "010"=>	dig_r<="11011111";		--ѡ��������������ʾ
		WHEN "011"=>	dig_r<="11101111";		--ѡ����ĸ��������ʾ
		WHEN "100"=>	dig_r<="11110111";		--ѡ�������������ʾ
		WHEN "101"=>	dig_r<="11111011";		--ѡ��������������ʾ
		WHEN "110"=>	dig_r<="11111101";		--ѡ����߸��������ʾ
		WHEN "111"=>	dig_r<="11111110";		--ѡ��ڰ˸��������ʾ
		END CASE;
	END IF;
END PROCESS;

PROCESS(disp_dat)
BEGIN
	CASE disp_dat IS
		WHEN 	X"0"=>	seg_r<=X"c0";--��ʾ0
		WHEN	X"1"=>	seg_r<=X"f9";--��ʾ1
		WHEN	X"2"=>	seg_r<=X"a4";--��ʾ2
		WHEN	X"3"=>	seg_r<=X"b0";--��ʾ3
		WHEN	X"4"=>	seg_r<=X"99";--��ʾ4
		WHEN	X"5"=>	seg_r<=X"92";--��ʾ5
		WHEN	X"6"=>	seg_r<=X"82";--��ʾ6
		WHEN	X"7"=>	seg_r<=X"f8";--��ʾ7
		WHEN	X"8"=>	seg_r<=X"80";--��ʾ8
		WHEN	X"9"=>	seg_r<=X"90";--��ʾ9
		WHEN	X"a"=>	seg_r<=X"88";--��ʾa
		WHEN	X"b"=>	seg_r<=X"83";--��ʾb
		WHEN	X"c"=>	seg_r<=X"c6";--��ʾc
		WHEN	X"d"=>	seg_r<=X"a1";--��ʾd
		WHEN	X"e"=>	seg_r<=X"86";--��ʾe
		WHEN	X"f"=>	seg_r<=X"8e";--��ʾf
	END CASE;
END PROCESS;
END;
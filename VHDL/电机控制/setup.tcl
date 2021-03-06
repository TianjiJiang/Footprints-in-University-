set_global_assignment -name FAMILY "Cyclone III"
set_global_assignment -name DEVICE EP3C55F484C8
set_global_assignment -name RESERVE_ALL_UNUSED_PINS "AS INPUT TRI-STATED"
set_global_assignment -name RESERVE_ALL_UNUSED_PINS_NO_OUTPUT_GND "AS INPUT TRI-STATED"
# system clock and reset----------------------------------------------------------------
set_location_assignment PIN_T2    -to clock
# led-----------------------------------------------------------------------------------
set_location_assignment PIN_F13   -to led[0]
set_location_assignment PIN_D10   -to led[1]
set_location_assignment PIN_E10   -to led[2]
set_location_assignment PIN_D8    -to led[3]
set_location_assignment PIN_C17   -to led[4]
set_location_assignment PIN_E12   -to led[5]
set_location_assignment PIN_E13   -to led[6]
set_location_assignment PIN_E11   -to led[7]
# peripheral-----------------------------------------------------------------------------
set_location_assignment PIN_AB11  -to key[0]
set_location_assignment PIN_AA11  -to key[1]
set_location_assignment PIN_T21   -to key[2]
set_location_assignment PIN_T22   -to key[3]
set_location_assignment PIN_H21   -to speed
set_location_assignment PIN_H22   -to motoa
set_location_assignment PIN_J21   -to motob
set_location_assignment PIN_D18   -to seg[0]
set_location_assignment PIN_C19   -to seg[1]
set_location_assignment PIN_D19   -to seg[2]
set_location_assignment PIN_A20   -to seg[3]
set_location_assignment PIN_C20   -to seg[4]
set_location_assignment PIN_B21   -to seg[5]
set_location_assignment PIN_B22   -to seg[6]
set_location_assignment PIN_D20   -to seg[7]
set_location_assignment PIN_C21   -to dig[0]
set_location_assignment PIN_D22   -to dig[1]
set_location_assignment PIN_D21   -to dig[2]
set_location_assignment PIN_F17   -to dig[3]
set_location_assignment PIN_H17   -to dig[4]
set_location_assignment PIN_H16   -to dig[5]
set_location_assignment PIN_J17   -to dig[6]
set_location_assignment PIN_K17   -to dig[7]
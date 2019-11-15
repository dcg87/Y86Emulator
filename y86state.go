package y86

type State struct {
	IP            uint32
	reg           []int32
	status        uint8
	ccode         []uint32
	SF            uint8
	OF            uint8
	ZF            uint8
	step          uint
	ADDRESS_SPACE *[]uint8
	mem_size      uint32
}

func state_CreateState(n_bytes uint32) *State {
	ADDRESS_SPACE := make([]uint8, n_bytes)

	state := State{IP: 0,
		reg:           []int32{0, 0, 0, 0, 0, 0, 0, 0},
		status:        0,
		ccode:         []uint32{0, 0, 0},
		SF:            0,
		OF:            0,
		ZF:            0,
		step:          0,
		ADDRESS_SPACE: &ADDRESS_SPACE,
		mem_size:      n_bytes}
	return &state

}

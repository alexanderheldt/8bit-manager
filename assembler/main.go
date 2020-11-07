package main

import "fmt"

const LCD = "00001111"

func main() {
	assembled := []string{
		// program
		fmt.Sprintf("%s %s", intToBinary(0), LCD),
		fmt.Sprintf("%s %s", intToBinary(1), intToBinary(42)),
		fmt.Sprintf("%s %s", intToBinary(2), LCD),
		fmt.Sprintf("%s %s", intToBinary(3), intToBinary(43)),
		fmt.Sprintf("%s %s", intToBinary(4), LCD),
		fmt.Sprintf("%s %s", intToBinary(5), intToBinary(44)),
		fmt.Sprintf("%s %s", intToBinary(6), LCD),
		fmt.Sprintf("%s %s", intToBinary(7), intToBinary(45)),
		fmt.Sprintf("%s %s", intToBinary(8), LCD),
		fmt.Sprintf("%s %s", intToBinary(9), intToBinary(46)),
		fmt.Sprintf("%s %s", intToBinary(10), LCD),
		fmt.Sprintf("%s %s", intToBinary(11), intToBinary(47)),
		fmt.Sprintf("%s %s", intToBinary(12), LCD),
		fmt.Sprintf("%s %s", intToBinary(13), intToBinary(48)),
		fmt.Sprintf("%s %s", intToBinary(14), LCD),
		fmt.Sprintf("%s %s", intToBinary(15), intToBinary(49)),
		fmt.Sprintf("%s %s", intToBinary(16), LCD),
		fmt.Sprintf("%s %s", intToBinary(17), intToBinary(50)),
		fmt.Sprintf("%s %s", intToBinary(18), LCD),
		fmt.Sprintf("%s %s", intToBinary(19), intToBinary(51)),
		fmt.Sprintf("%s %s", intToBinary(20), LCD),
		fmt.Sprintf("%s %s", intToBinary(21), intToBinary(52)),
		fmt.Sprintf("%s %s", intToBinary(22), LCD),
		fmt.Sprintf("%s %s", intToBinary(23), intToBinary(53)),
		fmt.Sprintf("%s %s", intToBinary(24), LCD),
		fmt.Sprintf("%s %s", intToBinary(25), intToBinary(54)),
		fmt.Sprintf("%s %s", intToBinary(26), LCD),
		fmt.Sprintf("%s %s", intToBinary(27), intToBinary(55)),
		fmt.Sprintf("%s %s", intToBinary(28), LCD),
		fmt.Sprintf("%s %s", intToBinary(29), intToBinary(56)),
		fmt.Sprintf("%s %s", intToBinary(30), LCD),
		fmt.Sprintf("%s %s", intToBinary(31), intToBinary(57)),
		fmt.Sprintf("%s %s", intToBinary(32), LCD),
		fmt.Sprintf("%s %s", intToBinary(33), intToBinary(58)),
		fmt.Sprintf("%s %s", intToBinary(34), LCD),
		fmt.Sprintf("%s %s", intToBinary(35), intToBinary(59)),
		fmt.Sprintf("%s %s", intToBinary(36), LCD),
		fmt.Sprintf("%s %s", intToBinary(37), intToBinary(60)),
		fmt.Sprintf("%s %s", intToBinary(38), LCD),
		fmt.Sprintf("%s %s", intToBinary(39), intToBinary(61)),

		fmt.Sprintf("%s %s", intToBinary(40), "00000110"), // JMP
		fmt.Sprintf("%s %s", intToBinary(41), intToBinary(24)),

		// variables
		fmt.Sprintf("%s %s", intToBinary(42), intToBinary(3)),
		fmt.Sprintf("%s %s", intToBinary(43), intToBinary(3)),
		fmt.Sprintf("%s %s", intToBinary(44), intToBinary(3)),
		fmt.Sprintf("%s %s", intToBinary(45), intToBinary(2)),  // function set 4-bit MSB
		fmt.Sprintf("%s %s", intToBinary(46), intToBinary(2)),  // function set 4-bit MSB (again)
		fmt.Sprintf("%s %s", intToBinary(47), intToBinary(0)),  // function set 4-bit LSB (NF** N = number of lines | F = font, 1/0 = 5x10/5x8 dots)
		fmt.Sprintf("%s %s", intToBinary(48), intToBinary(0)),  // display on/off control MSB
		fmt.Sprintf("%s %s", intToBinary(49), intToBinary(14)), // display on/off control LSB (14)
		fmt.Sprintf("%s %s", intToBinary(50), intToBinary(0)),  // clear display MSB
		fmt.Sprintf("%s %s", intToBinary(51), intToBinary(1)),  // clear display LSB
		fmt.Sprintf("%s %s", intToBinary(52), intToBinary(0)),  // Entry set MSB
		fmt.Sprintf("%s %s", intToBinary(53), intToBinary(6)),  // Entry set LSB
		fmt.Sprintf("%s %s", intToBinary(54), intToBinary(20)), // "A" (0100 0001) MSB with write set = 0001 0100 = 20;
		fmt.Sprintf("%s %s", intToBinary(55), intToBinary(17)), // "A" LSB with write set = 0001 0001 = 17;
		fmt.Sprintf("%s %s", intToBinary(56), intToBinary(22)), // "l" MSB (0110 1100)
		fmt.Sprintf("%s %s", intToBinary(57), intToBinary(28)), // "l" LSB
		fmt.Sprintf("%s %s", intToBinary(58), intToBinary(22)), // "e" MSB (0110 0101)
		fmt.Sprintf("%s %s", intToBinary(59), intToBinary(21)), // "e" LSB
		fmt.Sprintf("%s %s", intToBinary(60), intToBinary(23)), // "x" MSB (0111 1000)
		fmt.Sprintf("%s %s", intToBinary(61), intToBinary(24)), // "x" LSB
	}

	for _, line := range assembled {
		fmt.Println(line)
	}
}

func intToBinary(i int) string {
	return fmt.Sprintf("%08b", i)
}

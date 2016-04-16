package main
var a [10]int
var s = a[0:3:5]

func main() {

     for i:=0; i < 5; i++{
		s = append(s, 1000)
     }
	
	print(`Correct output should be
	Array s  [0 0 0 1000]
	Array a  [0 0 0 1000 0 0 0 0 0 0]
	Array s  [0 0 0 1000 1000]`)
	print(`
	Array a  [0 0 0 1000 1000 0 0 0 0 0]
	Array s  [0 0 0 1000 1000 1000]
	Array a  [0 0 0 1000 1000 0 0 0 0 0]
	Array s  [0 0 0 1000 1000 1000 1000]
	Array a  [0 0 0 1000 1000 0 0 0 0 0]`)
	print(`
	Array s  [0 0 0 1000 1000 1000 1000 1000]
	Array a  [0 0 0 1000 1000 0 0 0 0 0]
	Array s  [0 0 0 1000 1000 1000 1000 1000 1000]
	Array a  [0 0 0 1000 1000 0 0 0 0 0]`)
	print(`
	Array s  [0 0 0 1000 1000 1000 1000 1000 1000 1000]
	Array a  [0 0 0 1000 1000 0 0 0 0 0]
	Array s  [0 0 0 1000 1000 1000 1000 1000 1000 1000 1000]
	Array a  [0 0 0 1000 1000 0 0 0 0 0]`)
	print(`
	Array s  [0 0 0 1000 1000 1000 1000 1000 1000 1000 1000 1000]
	Array a  [0 0 0 1000 1000 0 0 0 0 0]
	`)
}
package main

type a struct{
  _ int;
  _ int;
  z int;
}

type b struct{
  _ int;
  _ int;
  z int;
}

type c []b;
func test(d c) b{
  var testing b;
  testing.z = 334444444
  var slicing c;
  slicing = append(slicing, testing)
  var glory struct{
  _ int
  _ int
  z int;
	};
  return glory
}

func main(a int) int{
	var woo []b
	test(woo);
}
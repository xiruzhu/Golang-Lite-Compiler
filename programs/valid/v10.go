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

type hue int

func booty(www int) hue{
	var test b;
	var woo []b
	woo = append(woo, test);
	woo[0].z = www
	woo = append(woo, woo[0]);
	return 0
}

func main() {
	println("Hello, 世界")
	var woo []b
	test(woo);
}
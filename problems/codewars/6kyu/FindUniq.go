package main

func FindUniq(arr []float32) float32 {
	var target float32
	if arr[0] == arr[1] {
		target = arr[0]
	} else if arr[1] == arr[2] {
		return arr[0]
	} else {
		return arr[1]
	}

	for _, i := range arr {
		if i != target {
			return i
		}
	}

	return float32(-1)
}

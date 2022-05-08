func century(year int) int {
	years := year % 100
	year -= years
	year /= 10
	if years > 0 {
		return year + 1
	}
	return year
}
import "strings"

func ReverseWords(str string) string {
	words := strings.Split(str, " ")
	var output []string
	for _, word := range words {
		runes := []rune(word)
		for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
			runes[i], runes[j] = runes[j], runes[i]
		}
		output = append(output, string(runes))
	}
	return strings.Join(output, " ")
}

import "strings"

func DnaToRna(string dna) string {
	return strings.Replace(dna, "T", "U", -1)
}
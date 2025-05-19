package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	var windowCount int
	for windowCount < 1 {
		fmt.Print("Введите количество окон: ")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)
		count, err := strconv.Atoi(input)
		if err != nil || count < 1 {
			fmt.Println("Количество окон должно быть больше 0.")
			continue
		}
		windowCount = count
	}

	type Window struct {
		totalTime int
		clients   []string
	}

	type Client struct {
		name string
		time int
	}

	windowQueues := make([]Window, windowCount)
	var clients []Client
	numberOfClients := 0

	for {
		fmt.Print("Введите команду (ENQUEUE, DISTRIBUTE): ")
		cmdInput, _ := reader.ReadString('\n')
		command := strings.ToUpper(strings.TrimSpace(cmdInput))

		switch command {
		case "ENQUEUE":
			numberOfClients++
			fmt.Print("Введите время обслуживания клиента: ")
			timeInput, _ := reader.ReadString('\n')
			timeInput = strings.TrimSpace(timeInput)
			t, err := strconv.Atoi(timeInput)
			if err != nil || t < 1 {
				fmt.Println("Время должно быть больше 0.")
				continue
			}
			clientName := fmt.Sprintf("T%d", numberOfClients)
			clients = append(clients, Client{name: clientName, time: t})

		case "DISTRIBUTE":
			if len(clients) == 0 {
				fmt.Println("Нет клиентов в очереди.")
				continue
			}

			// Сортировка клиентов по убыванию времени
			sort.Slice(clients, func(i, j int) bool {
				return clients[i].time > clients[j].time
			})

			// Распределение клиентов по наименее загруженным окнам
			for _, client := range clients {
				bestIndex := 0
				bestTime := windowQueues[0].totalTime
				for i := 1; i < windowCount; i++ {
					if windowQueues[i].totalTime < bestTime {
						bestIndex = i
						bestTime = windowQueues[i].totalTime
					}
				}
				windowQueues[bestIndex].totalTime += client.time
				windowQueues[bestIndex].clients = append(windowQueues[bestIndex].clients, client.name)
			}

			// Вывод результатов и завершение
			fmt.Println("\nРаспределение клиентов по окнам:")
			for i, window := range windowQueues {
				fmt.Printf("Окно %d (%d мин): ", i+1, window.totalTime)
				for _, client := range window.clients {
					fmt.Print(client, " ")
				}
				fmt.Println()
			}
			return

		default:
			fmt.Println("Неизвестная команда. Введите ENQUEUE или DISTRIBUTE.")
		}
	}
}

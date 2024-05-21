using Google.Apis.Auth.OAuth2;
using Google.Apis.Services;
using Google.Apis.Sheets.v4;
using Google.Apis.Sheets.v4.Data;
using Google.Apis.Util.Store;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Threading.Tasks;

namespace SwordEnhancement
{
    class Program
    {
        static string spreadsheetId = "1xlx4gDohutZTMRaaF5IG6alvnAH2S4asyXSjuvUV8tc";
        static SheetsService service;

        static void Main(string[] args)
        {
            Console.WriteLine("아이디를 입력해주세요");
            string userId = Console.ReadLine();

            service = InitializeGoogleSheetsService();

            try
            {
                int rowIndex = RetrieveUserData(userId);
                if (rowIndex == -1)
                {
                    // 새로운 사용자이므로 게임을 시작합니다.
                    StartNewGame(userId);
                }
                else
                {
                    // 기존 사용자이므로 이어서 게임을 진행합니다.
                    PlayGame(userId, rowIndex);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("오류: " + ex.Message);
            }
        }

        static SheetsService InitializeGoogleSheetsService()
        {
            string[] Scopes = { SheetsService.Scope.Spreadsheets };
            return new SheetsService(new BaseClientService.Initializer()
            {
                HttpClientInitializer = GoogleWebAuthorizationBroker.AuthorizeAsync(
                    new ClientSecrets
                    {
                        ClientId = "YourActualClientId",
                        ClientSecret = "YourActualClientSecret"
                    },
                    Scopes,
                    "user",
                    CancellationToken.None,
                    new FileDataStore("MyAppsToken")).Result,
                ApplicationName = "Google Sheets API .NET Quickstart",
            });
        }

        static int RetrieveUserData(string userId)
        {
            string range = "Gamedata!A1:Q";
            SpreadsheetsResource.ValuesResource.GetRequest getRequest = service.Spreadsheets.Values.Get(spreadsheetId, range);
            ValueRange getResponse = getRequest.Execute();
            IList<IList<object>> userData = getResponse.Values;

            int rowIndex = 0;
            foreach (var row in userData)
            {
                if (row.Count > 0 && row[0].ToString() == userId)
                {
                    return rowIndex;
                }
                rowIndex++;
            }

            return -1; // 사용자 데이터를 찾을 수 없음
        }

        static void StartNewGame(string userId)
        {
            // 새로운 사용자 데이터를 시트에 추가하고 게임을 시작합니다.
            List<object> newUserRow = new List<object>
            {
                userId, 1, 95.0, 0.0, 100, 5000000, 0, 0, 0, 0, 0, 0, 0, 0 // 단계별 시도 및 성공 횟수 초기화
            };
            ValueRange appendRequest = new ValueRange { Values = new List<IList<object>> { newUserRow } };
            string appendRange = $"Gamedata!A{userData.Count + 1}:Q{userData.Count + 1}";
            SpreadsheetsResource.ValuesResource.AppendRequest request = service.Spreadsheets.Values.Append(appendRequest, spreadsheetId, appendRange);
            request.ValueInputOption = SpreadsheetsResource.ValuesResource.AppendRequest.ValueInputOptionEnum.USERENTERED;
            var appendResponse = request.Execute();

            PlayGame(userId, userData.Count, service);
        }

        PlayGame(UserId, rowIndex, service);
    }
    catch (Exception ex)
    {
    Console.WriteLine("오류: " + ex.Message);
}
}
        static void PlayGame(string UserId, int rowIndex, SheetsService service, string formattedPlayTime)
{

    int enhancementLevel = 1;
    double successRate = 95.0;
    double destructionRate = 0.0;
    double enhancementCost = 100;
    double money = 5000000;  // 초기 금액 설정

    Console.WriteLine("게임을 시작합니다.");
    bool playing = true;
    while (playing && enhancementLevel < 25 && money >= enhancementCost)
    {
        double sellPrice = enhancementLevel >= 5 ? enhancementCost * 3 : 0;
        DisplayStatus(enhancementLevel, successRate, destructionRate, enhancementCost, sellPrice, money);

        Console.WriteLine("강화를 시도하시겠습니까? (예: y, 판매: s, 저장 후 종료: n)");
        string userInput = Console.ReadLine();

        switch (userInput.ToLower())
        {
            case "y":
                money -= enhancementCost;
                Random rnd = new Random();
                double chance = rnd.NextDouble() * 100;

                if (chance <= successRate)
                {
                    enhancementLevel++;
                    successRate -= 5; // 성공률 감소
                    enhancementCost *= 1.5; // 비용 증가
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine("성공! 검이 강화되었습니다.");
                    Console.ResetColor();
                    if (enhancementLevel >= 15)
                    {
                        destructionRate = Math.Min((enhancementLevel - 14) * 5, 95); // 파괴 확률 증가
                    }
                }
                else if (chance <= successRate + destructionRate)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("파괴! 검이 파괴되었습니다.");
                    Console.ResetColor();
                    enhancementLevel = 1;
                    successRate = 95.0;
                    destructionRate = 0.0;
                    enhancementCost = 100;
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine("실패... 다음 기회에.");
                    Console.ResetColor();
                }
                break;
            case "s":
                if (enhancementLevel >= 5)
                {
                    money += sellPrice;
                    Console.WriteLine($"검을 판매했습니다. {sellPrice:F0}원을 획득하였습니다.");
                    enhancementLevel = 1;
                    successRate = 95.0;
                    enhancementCost = 100;
                    destructionRate = 0.0;
                }
                break;
            case "n":
                UpdateUserData(UserId, rowIndex, service, enhancementLevel, successRate, destructionRate, enhancementCost, money);
                playing = false;
                Console.WriteLine("게임을 종료합니다.");
                break;
        }

        if (money < enhancementCost)
        {
            Console.WriteLine("돈이 부족합니다. 돈을 충전하거나 검을 판매하세요.");
            // 충전 또는 판매 로직 구현
        }
    }

    if (enhancementLevel == 25)
    {
        Console.WriteLine("축하합니다! 25단계까지 성공적으로 강화했습니다!");
    }
}

static void MoneyOptions(ref double money, int enhancementLevel, double enhancementCost)
{
    // 돈 충전 또는 검 판매 옵션 제공 로직
    Console.WriteLine("1000을 입력하여 1,000,000원을 충전할 수 있습니다. (종료: n)");
    Console.WriteLine("10000을 입력하여 5,000,000원을 충전할 수 있습니다. (종료: n)");
    string input = Console.ReadLine();

    switch (input)
    {
        case "1000":
            money += 1000000;
            Console.WriteLine("1,000,000원이 충전되었습니다.");
            break;
        case "10000":
            money += 5000000;
            Console.WriteLine("5,000,000원이 충전되었습니다.");
            break;
        case "n":
            Console.WriteLine("충전을 취소합니다.");
            break;
        default:
            Console.WriteLine("잘못된 입력입니다.");
            break;
    }
}

static void DisplayStatus(int enhancementLevel, double successRate, double destructionRate, double enhancementCost, double sellPrice, double money)
{
    Console.WriteLine($"현재 강화 단계: {enhancementLevel}");
    Console.WriteLine($"현재 강화 비용: {enhancementCost:F2}원");
    Console.WriteLine($"현재 성공률: {successRate}%");
    Console.WriteLine($"파괴 확률: {destructionRate}%");
    Console.WriteLine($"판매 가격: {sellPrice:F2}원");
    Console.WriteLine($"남은 돈: {money:F2}원");
}

    }
}
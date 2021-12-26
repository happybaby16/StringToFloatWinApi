#include <Windows.h>
#include <math.h>
#include <wchar.h>

#define PATHIN L"input.txt"
#define PATHOUT L"output.txt"

#define STR_EQUAL 0


struct Answer
{
	FLOAT x1;
	FLOAT x2;
	FLOAT D;
	DWORD count;
};


struct DataQuadraticSTR
{
	LPWSTR a;
	LPWSTR b;
	LPWSTR c;
	LPWSTR res;
};

struct DataQuadraticFLOAT
{
	FLOAT a;
	FLOAT b;
	FLOAT c;
	FLOAT res;
};


struct Answer quadratic(FLOAT a, FLOAT b, FLOAT c, FLOAT res)
{
	struct Answer result = { 0, 0, -1,0 };
	c = c - res;
	if (a != 0 && b != 0)
	{
		FLOAT D = (pow(-b, 2)) - (4 * (a * c));
		if (D > 0)
		{
			result.D = D;
			result.x1 = (-b + sqrt(D)) / (2 * a);
			result.x2 = (-b - sqrt(D)) / (2 * a);
			result.count = 2;
			return result;
		}
		if (D == 0)
		{
			result.D = D;
			result.x1 = (-b + sqrt(D)) / (2 * a);
			result.count = 1;
			return result;
		}
		if (D < 0)
		{
			result.D = D;
			result.count = 0;
			return result;
		}
	}
	if (a != 0 && b == 0)
	{
		result.count = 0;

		_try
		{
			if (-c >= 0)
			{
			result.x1 = -sqrt(-c / a);
			result.count = result.count + 1;
			}
		}
			_except(EXCEPTION_CONTINUE_SEARCH)
		{
			result.x1 = 0;
		}


		_try
		{
			if (-c >= 0)
			{
			result.x2 = sqrt(-c / a);
			result.count = result.count + 1;
			}
		}
			_except(EXCEPTION_CONTINUE_SEARCH)
		{
			result.x2 = 0;
		}

		return result;


	}

	if (a == 0 && b != 0)
	{
		result.x1 = -c / b;
		result.count = 1;
		return result;
	}


	if (a == 0 && b == 0)
	{
		result.count = 0;
		return result;
	}
	return result;

};






struct DataQuadraticSTR readFile(struct DataQuadraticSTR data)
{
	HANDLE hFile = CreateFile(PATHIN,
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ,
					NULL,
					OPEN_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL);


	DWORD d = 0;
	DWORD d1 = 0;
	OVERLAPPED olf = { 0 };
	DWORD sizeBuffer = 512;
	LPSTR str = malloc(sizeBuffer + 1);
	ReadFile(hFile, str, sizeBuffer, &d, &olf);
	free(str);
	olf.Offset = 0;//задаем смещение (позицию в файле)
	LPSTR str1 = malloc(d + 1);

	ReadFile(hFile, str1, d, &d1, &olf);

	str1[d1] = '\0';


	int k = 0;
	for (k = 0; k<4;k++)
	{
		LPSTR a = malloc(d1);
		for (int i = 0; i < d1; (str1)++)
		{
			CHAR f = *str1;
			if (f == ' ')
			{
				a[i] = '\0';
				(str1)++;
				break;
			}
			a[i] = f;
			i++;
		}
		if (k == 0) data.a = a;
		if (k == 1) data.b = a;
		if (k == 2) data.c = a;
		if (k == 3) data.res = a;
	}
	return data;
	
}







void writeFile(struct Answer ans)
{
	HANDLE hFile = CreateFile(PATHOUT,
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ,
					NULL,
					OPEN_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL);

	if (ans.count == 0)
	{
		DWORD d = 0;
		LPCSTR str = "Kornei net";
		WriteFile(hFile,//дескриптор открытого файла
			str,//указываем буфер для записи
			strlen(str), //указываем, сколько байт мы хотим записать
			&d,//передаем указатель на DWORD
			NULL//синхронный режим записи
		);
	}
	if (ans.count == 1 && ans.D!=-1)
	{
		DWORD d = 0;
		LPCSTR str = "D = 0\n";
		WriteFile(hFile,
			str,
			strlen(str),
			&d,
			NULL
		);


		d = 0;
		str = "x = ";
		WriteFile(hFile,
			str,
			strlen(str) , 
			&d,
			NULL
		);

		d = 0;
		FLOAT x = ans.x1;
		TCHAR a[15];
		swprintf(a, 15, TEXT("%f"), x);
		WriteFile(hFile,
			a,
			15,
			&d,
			NULL
		);

	}
	if (ans.count == 1 && ans.D == -1)
	{
		DWORD d = 0;
		LPCSTR str = "x = ";
		WriteFile(hFile,
			str,
			strlen(str), 
			&d,
			NULL
		);

		d = 0;
		FLOAT x = ans.x1;
		TCHAR a[15];
		swprintf(a, 15, TEXT("%f"), x);
		WriteFile(hFile,
			a,
			15, 
			&d,
			NULL
		);
	}
	if (ans.count == 2)
	{
		DWORD d = 0;
		LPCSTR str = "D = ";
		if (ans.D != -1)
		{
			DWORD d = 0;
			LPCSTR str = "D = ";
			WriteFile(hFile,
				str,
				strlen(str),
				&d,
				NULL
			);

			d = 0;
			FLOAT D = ans.D;
			TCHAR a[20];
			swprintf(a, 20, TEXT("%f"), D);
			WriteFile(hFile,
				a,
				20,
				&d,
				NULL
			);
		}

		d = 0;
		str = "\nx1 = ";
		WriteFile(hFile,
			str,
			strlen(str),
			&d,
			NULL
		);

		d = 0;
		FLOAT x1 = ans.x1;
		TCHAR b[17];
		swprintf(b, 17, TEXT("%f"), x1);
		WriteFile(hFile,
			b,
			17, 
			&d,
			NULL
		);

		d = 0;
		str = "\nx2 = ";
		WriteFile(hFile,
			str,
			strlen(str), 
			&d,
			NULL
		);

		d = 0;
		FLOAT x2 = ans.x2;
		TCHAR c[16];
		swprintf(c, 16, TEXT("%f"), x2);
		WriteFile(hFile,
			c,
			16, 
			&d,
			NULL
		);
	}
}



FLOAT stringToFloat(LPWSTR number)
{
	DWORD lenght = strlen(number);

	LPSTR str1 = malloc(lenght + 1);
	str1 = number;
	LPSTR str2 = str1;
	BOOL minus = FALSE;
	if (str1[0] == '-')
	{
		str2[0] = '0';
		minus = TRUE;
	}
	
	FLOAT before_point = 0.0f;
	FLOAT after_point = 0.0f;

	
	

	
	DWORD BFP_leght = 0;
	DWORD AFP_leght = 0;


	for (DWORD i = 0; i<lenght; (str1)++)
	{
		CHAR s1 = *str1;
		if (s1 == L'.')
		{
			BFP_leght = i;
			AFP_leght = lenght - i-1;
			break;
		}
		BFP_leght = i;
		i++;
	}

	BFP_leght -= 1;

	if (AFP_leght == 0)
	{
		BFP_leght += 2;
		DWORD power = BFP_leght-1;
		str1 = str2;
		for (DWORD i = 0; i < BFP_leght; (str1)++)
		{
			CHAR s1 = *str1;
			if (s1 != L'.')
			{
				DWORD f1 = s1 - '0';
				before_point += f1 * pow(10, power);
				power--;
				i++;
			}
		}

		if (minus) before_point = before_point * (-1);
		return before_point;
	}

	str1 = str2;
	for (DWORD i = 0; i < lenght; (str1)++)
	{
		CHAR s1 = *str1;
		if (s1!=L'.')
		{
			DWORD f1 = s1 - '0';
			before_point += f1 * pow(10, BFP_leght);
			BFP_leght--;
		}
		
		if (s1 == L'.')
		{
			(str1)++;
			DWORD power = 1;
			for (DWORD j = 0; j < AFP_leght; (str1)++)
			{
				CHAR s1 = *str1;
				if (j % 2 == 0)
				{
					DWORD f1 = s1 - '0';
					after_point += f1 / pow(10, power);
					power++;
				}
				j++;
			}
			break;
		}
		i++;
	}


	if (minus) { before_point = before_point * (-1);  after_point = after_point * (-1); };
	return before_point + after_point;

}








int WINAPI WinMain(HINSTANCE hlnstance, // дескриптор, присваиваемый запущенному приложению

	HINSTANCE hPrevInstance, // для совместимости с winl6. в Win32 не используется

	LPSTR lpCmdLine, // указатель на командною строку, если приложение так запущено

	int nCmdShow) // значение, которое может быть передано в функцию Show Window ()
{

	struct DataQuadraticSTR data = { L"0",L"0",L"0",L"0" };
	data = readFile(data);

	if (data.a == L"" || data.b == L"" || data.c == L"" || data.res == L"")
	{
		MessageBox(NULL, L"Введены некорректные данные", L"Ошибка", NULL);
	}
	else
	{
		struct DataQuadraticFLOAT dataFloat = { 0,0,0,0 };

		FLOAT a = stringToFloat(data.a);
		FLOAT b = stringToFloat(data.b);
		FLOAT c = stringToFloat(data.c);
		FLOAT res = stringToFloat(data.res);
		if (isinf(a)||isinf(b) || isinf(c) || isinf(res))
		{
			MessageBox(NULL, L"Введены некорректные данные", L"Ошибка", NULL);
		}
		else
		{
			struct Answer ans = quadratic(a,b,c,res);
			writeFile(ans);
		}
	}
	return 0;



}
# akshare是一个用于获取股票市场的包，可进行简单的排序等操作
import akshare as ak
import pandas as pd
'''
    该代码用于获取并处理股票信息，供同学们参考
    处理后的股票数据文件已给出，名为“Top96_A_Lite”，格式为CSV文件
    由于股票市场变动频繁，为保证统一，请同学们统一提供的“Top96_A_Lite”文件。
'''

# 获得A股股票信息
stock_zh_a_spot_df = ak.stock_zh_a_spot_em()
print(stock_zh_a_spot_df.head())
# 按照总市值排序，获得Top100排行榜
stock_zh_a_spot_df_sorted = stock_zh_a_spot_df.sort_values(by="总市值", ascending=False)
top_100_market_value = stock_zh_a_spot_df_sorted.head(100)
# 查询市值Top 100的公司
print(top_100_market_value)
top_100_market_value.to_csv("Top100_A")

file_path = 'Top100_A'
data = pd.read_csv(file_path, usecols=['代码', '名称', '最新价', '年初至今涨跌幅'])
# 删除满足特定查询条件的行
# 删除满足某条件的所有行
# 直接在原DataFrame上操作
data.dropna(subset=['最新价'], axis=0, inplace=True)
data['成本价'] = data['最新价'] / (1 + data['年初至今涨跌幅'] / 100)
print(data.head())
data.to_csv('Top'+ str(len(data)) + '_A_Lite', index=False)

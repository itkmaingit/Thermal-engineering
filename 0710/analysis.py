import pandas as pd

# csvファイル名
input_filename = 'data.csv'

# データの読み込み
df = pd.read_csv(input_filename)

# 国ごとにデータを抽出し、新しいcsvファイルに保存
for country, group in df.groupby('Country'):
    if len(group)>3:
        # Rankを再度設定
        group['Rank'] = range(1, len(group) + 1)
        # 新しいcsvファイルに保存
        group[['Rank', 'Rmax']].to_csv(f'{country}.csv', index=False)

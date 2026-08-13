# 학생 점수 데이터 및 합격 기준 설정
scores = [78, 85, 92, 68, 95, 88, 74]
PASS_SCORE = 80

# 1. 기본 통계 계산 (평균, 최고, 최저)
average = sum(scores) / len(scores)
highest = max(scores)
lowest = min(scores)

# 2. 조건별 데이터 필터링
# 80점 이상인 점수만 추출
high_scores = [score for score in scores if score >= PASS_SCORE]

# 평균 이상인 학생 수 카운트
above_average_count = sum(1 for score in scores if score >= average)

# 3. 결과 데이터 취합
result = {
    "average": average,
    "highest": highest,
    "lowest": lowest,
    "high_scores": high_scores,
    "above_average_count": above_average_count
}

# 4. 결과 출력
print(f"평균 점수 : {result['average']:.2f}")  # 소수점 둘째 자리까지 깔끔하게 출력
print(f"최고점 : {result['highest']}")
print(f"최저점 : {result['lowest']}")
print(f"80점 이상 리스트 : {result['high_scores']}")
print(f"평균 이상인 학생 수 : {result['above_average_count']}")
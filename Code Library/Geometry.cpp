struct Geometry{
	ll x, y, id; 
	//象限判定
	ll quad() const{
		if(x > 0 && y >= 0) return 1;
		if(x <= 0 && y > 0) return 2;
		if(x < 0 && y <= 0) return 3;
		return 4;
	}
	
	ll cross(const Geometry& other) const{
		return x * other.y - y * other.x;
	}
	// 偏角ソート用
  bool operator<(const Geometry& other) const {
    int q1 = quad(), q2 = other.quad();
    if (q1 != q2) return q1 < q2;
    return cross(other) > 0; // 反時計回りが正
  }

    // 同じ方向にいるか
  bool is_same_dir(Geometry& other) const {
    return quad() == other.quad() && cross(other) == 0;
  }
};


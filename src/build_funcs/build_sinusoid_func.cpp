void 												
World::Build(void) {
    int num_samples = 16;

    vp_.SetHRes(512);
	vp_.SetVRes(512);
	vp_.SetPixelSize(0.040);
    vp_.SetSampler(new MultiJittered(num_samples));
	vp_.SetGamma(1.0);
	
	background_color_ = kWhite;
	
    auto ray_func = [](Ray ray) {
        double f = 0.5 * (1 + sin(ray.o_.x_ * ray.o_.x_ * ray.o_.y_ * ray.o_.y_));
        return RGBColor(f); 
    };
    Function *func_tracer = new Function(this);
    func_tracer->SetFunction(ray_func);

    tracer_ptr_ = func_tracer;
}

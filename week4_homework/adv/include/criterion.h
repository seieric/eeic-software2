// 損失関数
#pragma once

double cross_entropy_loss(double pred, double ans);
double dcross_entropy_loss_dpred(double pred, double ans);
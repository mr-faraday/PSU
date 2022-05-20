import { createRouter, createWebHistory } from 'vue-router'
import dashboardItems from './dashboard'

/**
 * @type {import('vue-router').RouteRecordRaw[]}
 */
const routes = [
  {
    path: '/login',
    name: 'login',
    component: () => import('@views/LoginView.vue'),
  },
  {
    path: '/dashboard',
    name: 'dashboard',
    component: () => import('@views/DashboardView.vue'),
    children: dashboardItems.map((item) => ({
      path: item.href,
      name: `dashboard-${item.name}`,
      component: () => import(`@views/dashboard/${item.component}`),
      meta: item.meta,
    })),
  },

  { path: '/:pathMatch(.*)*', component: () => import('@views/IndexView.vue') },
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
  linkActiveClass: 'active',
})

export default router

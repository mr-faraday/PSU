import { createRouter, createWebHistory } from 'vue-router'

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
  },

  { path: '/:pathMatch(.*)*', component: () => import('@views/IndexView.vue') },
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
  linkActiveClass: 'active',
})

export default router
